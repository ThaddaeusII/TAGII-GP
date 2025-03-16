# Linear Genetic Programming System

Author: Thad Greiner

This is my personal LGP system for evolving agents for the Ant Trail problem. It is built to be customizable and efficient, with the goal of expanding upon problems like the Santa Fe Ant Trail while keeping runtimes low.

## Installation

```
git clone --recurse-submodules https://github.com/ThaddaeusII/LGPSystem.git
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

### 2. Default Operators
The operators are as follows:
* PROG3: runs the three parameters sequentially.
* PROG2: runs the two parameters sequentially, just like PROG3.
* LOOK: Checks if there is food in front of the agent. If yes, runs parameter 1, else parameter 2.
* move: moves the agent one space forward.
* turn_left: turns the agent left.
* turn_right: turns the agent right.
* special case: if a referenced instruction doesn't exist, treated as a do-nothing terminal.

All terminal operators consume 1 time step.

### 3. Execution

```
[1]: [0, PROG3, (I, 0), (T, turn_left), (I, 1)]
[2]: [2, PROG3, (I, 1), (T, move), (I, 0)]
[3]: [1, PROG2, (I, 2), (I, 1)]
[4]: [1, LOOK, (T, turn_left), (T, turn_right)]
```

Execution is NOT purely sequential. The program starts with the first instruction, the ```PROG3``` on ```line 1``` above. It starts by running ```(I, 0)```, which means run the first instruction after line 1 with reference = 0. No instructions after the first line have reference 0, so nothing is done. Next it runs the turn_left terminal operator. Finally, it runs instruction reference 1, the first being line 3. Thus, line 2 is never used. Line 3 will do nothing for the first parameter and then run line 4 for the second. Line 4 will check if there is food in front of the agent: if so, turn left, else turn right. Overall, the program does nothing 2 times and turns 2 times, totaling at 4 steps. Thus, if the max number of steps hasn't bee reached, it will execute again from the start until max steps have been reached. Note, it will stop midway through if max steps were hit before reaching the end.

### 4. Mutation, Crossover, and Selection

--- ***INCOMPLETE*** ---

## Using the System

### 1. Editing the Build
To run the system using the default build, simply run ```make``` and ```./evolve```. There are additional options such as ```make debug```, ```make clean```, and ```make slow``` (no optimization). If extra files are desired, add the relevant cpp files and include paths to the ```Makefile```.

### 2. Editing the Basic Parameters
Edit the ```main.cpp``` to change the system parameters and/or add additional features, all parameters of the run are commented. You can change population size, generations, how large initial programs can be, how many steps can be run, and set the environment file.

### 3. Editing the Environment
See ```Environments/test.env```. The first line should have ```sizeX, sizeY, startX, startY, direction```. After that you should construct a 2D grid of size (sizeX, sizeY) where X is # of columns, Y is # of rows, '0's are empty space, and '1's are food. You can swap the filepath when calling the ```GPSystem::run()``` function.

### 4. Adding New Operators
The system was built for somewhat easy additions of operators, both control and terminals. To do so, you need to follow two steps:

1. Add a new operator class (.h and .cpp) to the ```Operators/``` folder. It should inherit from either ```TerminalOperator.h``` or ```ControlOperator.h```, and needs to initialize their pure virtual functions. In general, you need an ```execute()``` and ```display()``` function for both. ```ControlOperator``` also needs a ```randomize()``` function to initialize the parameters randomly. For example, if you need 2 parameters exactly, make sure initialize exactly 2. Or, if you want only terminals as parameters, you can enforce that. See the existing operators for examples.
2. To make adding the new operators easy, there is a ```OperatorRegistry``` class in the ```System/``` folder. Once you have a new operator class made, navigate to ```OperatorRegistry.cpp``` and register it as either a ```ControlOperator``` or ```TerminalOperator``` in the ```registerAllOperators()``` function. You will also need to add the respective include: ```#include "YourOperator.h"```. Once you have done so, you are all set as it has been automatically added to the pool. By default, each group of operators has a uniform chance of being randomly chosen (Control and Terminal are seperate, and have a 50/50 when having to choose between them). You can modify these effects in the ```getRandomTerminalOperator()``` and ```getRandomControlOperator()``` functions, as well as your ```randomize()``` function.

### 4. Adding Genetic Operators

--- ***INCOMPLETE*** ---

## Citations

LGP language based on:
* "λ-LGP: an improved version of linear genetic programming evaluated in the Ant Trail problem" by Léo Françoso Dal Piccol Sotto, Vinícius Veloso de Melo,
Márcio Porto Basgalupp.

Third-Party software used:
* Empirical: https://github.com/devosoft/Empirical.git
