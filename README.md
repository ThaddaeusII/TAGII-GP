# TAGII-GP: Thad's Agent/Grid-based Interface for Instructional Genetic Programming

Author: Thad Greiner

This is my personal LGP system for evolving agents for a variety of (mostly) grid-based problems. It is built to be customizable and efficient, with the goal of expanding upon problems like the Santa Fe Ant Trail, maze solving, and Pacman.

## Installation

Note, you will need ```git```, ```g++``` or ```clang```, ```c++20```, and ```make``` to easily setup and use this project!

```
git clone --recurse-submodules https://github.com/ThaddaeusII/TAGII-GP.git
```

Navigate to ```Third-Party/Empirical/include/emp/base/_optional_throw.hpp```. On ```line 49```, change the function to ```inline```, which will make it as follows:

```inline void assert_print_first_opt(std::stringstream & ss, int placeholder) {;}```

## The Default LGP System

### 1. Program Format
Here is an example program generated and output:
```
[1]: [0, PROG3, (I, 0), (T, turn_left), (I, 1)]
[2]: [1, PROG3, (I, 1), (T, move), (I, 0)]
[3]: [1, PROG2, (I, 2), (I, 1)]
[4]: [1, LOOK, (T, turn_left), (T, turn_right)]
```

Each instruction has the following format: 

```
[line #]: [reference #, Control Operator, Parameters]
```

Each parameter has the following format:

```
(Instruction, reference #) or (Terminal, Terminal Operator)
```

### 2. Existing Operators
Here are the operators I currently have implemeneted:
* PROG#: runs the next # of parameters sequentially. Note, this # is specified when registering operators to an environment (see below).
* LOOK: Checks if there is food directly in front of the agent. If yes, runs parameter 1, else parameter 2. Deprecated, use LOOK_AHEAD going forward.
* LOOK_AHEAD: Similar to LOOK, but has a customizable name to allow for reuse (such as LOOK_FOOD, LOOK_WALL,and LOOK_PREDATOR).
* move: moves the agent one space forward.
* turn_left: turns the agent left.
* turn_right: turns the agent right.
* WAIT: if a referenced instruction doesn't exist, it is treated as a wait terminal.

### 3. Execution

```
[1]: [0, PROG3, (I, 0), (T, turn_left), (I, 1)]
[2]: [2, PROG3, (I, 1), (T, move), (I, 0)]
[3]: [1, PROG2, (I, 2), (I, 1)]
[4]: [1, LOOK, (T, turn_left), (T, turn_right)]
```

Execution is NOT purely sequential. The program starts with the first instruction, the ```PROG3``` on ```line 1``` above. It starts by running ```(I, 0)```, which means run the first instruction after line 1 with reference = 0. No instructions after the first line have reference 0, so nothing is done. Next it runs the turn_left terminal operator. Finally, it runs instruction reference 1, the first being line 3. Thus, line 2 is never used. Line 3 will do nothing for the first parameter and then run line 4 for the second. Line 4 will check if there is food in front of the agent: if so, turn left, else turn right. Overall, the program does nothing 2 times and turns 2 times, totaling at 4 steps. Thus, if the max number of steps hasn't bee reached, it will execute again from the start until max steps have been reached. Note, it will stop midway through if max steps were hit before reaching the end.

### 4. Mutation, Crossover, and Selection

By default, mutation is set to have a set of probablities to do certain things:
* User defines chance of a each instruction mutating: mutationRate.
* If an instruction mutates, it has the following probablity set
    * 50% chance to modify the current instruction
        * 50% chance to modidify parameters --- ***INCOMPLETE*** ---
        * 50% chance to randomize the operator (and parameters to match operator change)
    * 25% chance to add a random instruction at the current position
    * 25% chance to delete the current instruction

By default, crossover has a user defined chance, crossover chance. If no crossover, either parent is copied with equal probability. If crossover does occur, the following happens:
* An index is selected in each parent
* Parent 1 instructions from 0 to index 1 are copied to the child
* Parent 2 instructions from index 2 to end are copied to the child
* To prevent program size expansion, maxSize is set to 10 for each parent's copy --- ***ADJUST THIS*** ---

By default, selection uses tournament selection with tournament size 7 (set in the class). Selection will pick two best parents from a tournament (--- ***FIX*** ---, can select same parent, needs non-replacement), the performs cross over using the two. After creating a new child via crossover or copying a parent, the child will be mutated, then added to the next generation.

## Using the System

### 1. Editing the Build
To run the system using the default build, simply run ```make``` and ```./evolve```. There are additional options such as ```make debug```, ```make clean```, and ```make slow``` (no optimization). If extra files are desired, add the relevant cpp files and include paths to the ```Makefile```.

### 2. Editing the Basic Parameters
The user interface will bring up a simple terminal menu, where typing 1 will allow the user to see and modify the current parameters. This includes population size, muatation rate, generations, selection methods, enironments, etc. They can all be reconfigured in ```main.cpp```.

### 3. Editing the Environment
Environment files should follow the format of the specific environment class you are using. For Santa Fe Ant Trail, it should have ```sizeX, sizeY, startX, startY, direction``` on the first line. After that you should construct a 2D grid of size (sizeX, sizeY) where X is # of columns, Y is # of rows, '0's are empty space, and '1's are food. You can swap the filepath given, ```santafe.env```, or swap/add a new one in ```main.cpp```. Pacman, on the other hand, has a slighlty differnt format, which can be seen in ```pacman.env```.

### 4. Adding New Instruction Operators
The system was built for somewhat easy additions of operators, both control and terminals. To do so, you need to follow two steps:

1. Add a new operator class (.h and .cpp) to the ```Operators/``` folder. It should inherit from either ```TerminalOperator.h``` or ```ControlOperator.h```, and needs to initialize their pure virtual functions. In general, you need an ```execute()``` and ```display()``` function for both. ```ControlOperator``` also needs a ```randomize()``` function to initialize the parameters randomly and in the cirrect format, a ```mutate()``` function for modifying parameters, and a ```visualize()``` function for visualizing how a program acts on an environment.
2. To make adding the new operators easy, all you need to do is register them to an ```Environment``` class. Each ```Environment``` has a vector of control and terminal operators. By registering them in the ```RegisterAllOperators()``` function, they will added to the pool of randomly selectable operators to be randomized or mutated to. Registering them looks like this:

```
// Control Operators
registerControlOperator(std::make_shared<PROG>(*this, 2));
registerControlOperator(std::make_shared<PROG>(*this, 3));
registerControlOperator(std::make_shared<LOOK_AHEAD>(*this, [this](){ return this->pelletAhead(); }, "LOOK_PELLET"));
registerControlOperator(std::make_shared<LOOK_AHEAD>(*this, [this](){ return this->superPelletAhead(); }, "LOOK_SUPER_PELLET"));
registerControlOperator(std::make_shared<LOOK_AHEAD>(*this, [this](){ return this->ghostAhead(); }, "LOOK_GHOST"));

// Terminal Operators
registerTerminalOperator(std::make_shared<Move>(*this, [this](){ this->move(); }));
registerTerminalOperator(std::make_shared<Turn>(*this, [this](){ this->turnLeft(); }, true));
registerTerminalOperator(std::make_shared<Turn>(*this, [this](){ this->turnRight(); }, false));
```

By default, all operators need a reference to the environment, hence the *this. Outside of that, your custom operators can take whatever parameters they need. Avbove, the PROG operator takes the # of sequential commands to run, while the others take a function of the environment to bind. This means that when the Program calls the Move operator's execute, it is bound to the environment's move() function and will call it. Thus, if you want an operator to affect the environment on execution, you can bind as many functions as needed.

### 4. Adding Genetic Operators

Outside of new instructional operators, you can change also add new methods for selection, mutation, and crossover with ease. All three have a respetive base class (see the ```*Methods/``` folders), and each one has constructor that needs upcalled and a single virtual function to override. Mutation has ```mutate()``` to control how an individual program is changed, Crossover has ```cross()``` to determine how two parents create a child/children, and Selection takes both other methods and controls the whole process of how one generation creates the next via its ```select()``` function. Once a new method is created, it can be swapped in or added by adding them to ```main.cpp```.

### 5. Adding ENvironments

The the final and most complicated feature of the system is the ability to create and add environments with ease. Like before, there is a base class (see ```Environments/Envirnoment.h```), but it is more complicated than before. It also needs a constructor upcall to get the name, and also needs four functions: ```display()``` to show the environment, ```load()``` to load an environment form file, ```reset()``` to setup the environment for the next program, and ```registerAllOperators()``` to register all operators that can be used on the environment. It should also be added to ```main.cpp``` in order to use it.

In order for programs to be evaluated, it has 3 protected variables: fitness, curSteps, and maxSteps. Your selector can utilize that fitness (maximize or minimize) for program evolution, while maxSteps is how many "steps" are allocated to your program, and curSteps are how many remain. WHen a program starts/resets, it will have maxSteps, and won't stop until curSteps is less than or equal to zero. "Steps" are in quotes because the only provided means of step reduction is the WAIT command (unreferenced instruction), consuming one step. Any other means of modifiying steps is up to you, which is flexible, but does allow for infinite loops if not careful.

Outside of these requirements, the class is freely customizable. My examples and intent was for grid based worlds and simple navigation / collection games. However, you can get really creative with it, as it is possible to expand out of 2D, create complex world dynamics, or even create a register based "environment" with no actual grid. The possibilities are immense, which was my goal with the flexibility. 

### TODO

* Fixes:
    1. Add error checking for improper parameters and files entered.
    3. Add parameter modification to the given control operator ```mutate()``` functions instead of randomizing them.
    4. Improve the default crossover and mutation implementation.
    5. Get random sampling without replacement working for tournament selection.
* Enviroment Improvements
    1. Improve environment file format.
    2. Add maze solving environment
    3. Improve Pacman environment
* System Improvements
    1. Add more genetic operators (mutation, selection, crossover)
    2. Add more control and terminal operators
    3. Optimize the performance.
    4. Add GUI using wxWidgets for cross-platform support and better user experience.
    6. Add saving/loading feature for parameters and populations.
    7. Add parallelization / nvidia options.

## Citations

LGP language based on:
* "λ-LGP: an improved version of linear genetic programming evaluated in the Ant Trail problem" by Léo Françoso Dal Piccol Sotto, Vinícius Veloso de Melo,
Márcio Porto Basgalupp.

Third-Party software used:
* Empirical: https://github.com/devosoft/Empirical.git
