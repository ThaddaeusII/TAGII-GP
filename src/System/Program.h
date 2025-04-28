#pragma once

#include <vector>
#include <memory>
#include <deque>
#include <functional>
#include <tuple>

#include "Environment.h"
#include "ControlOperator.h"

class Crossover;
class Mutation;
class Selection;

class Program
{
private:
    struct Instruction
    {
        int reference = -1;
        std::shared_ptr<ControlOperator> op;
        std::vector<std::pair<int, int>> params;

        Instruction(std::shared_ptr<Environment> env, int count);
    };

    int fitness = -1;
    bool waitForInput = true;
    std::vector<std::unique_ptr<Instruction>> instructions;
    std::shared_ptr<Environment> env;
    std::deque<std::tuple<std::function<void()>, int, int>> executionQueue;

    int findReference(int pos, int ref);

    friend class Crossover;
    friend class Mutation;
    friend class Selection;

public:
    Program(std::shared_ptr<Environment> env);
    void initialize(int numInstructions);
    
    // Execution functions
    void execute();             // Runs whole sequence
    void start();               // Starts sequence
    void step();                // Single step
    void stepControl(int pos);  // Executes one control, the control will add params to execution queue
    void stepTerminal(int op);  // Executes one terminal, calls bound environment functor
    bool complete();            // Checks if program has reached max steps (or is empty)
    bool running();             // Checks if program execution queue is empty
    void reset();               // Resets program
    void wait();                // Wait instruction
    void evaluateFitness();     // Check fitness when done

    // Takes the scheduling line pos and instr param, will attempt to schedule it
    // DO NOT schedule first line (control #1), use Program::start()
    void scheduleInstructionFront(int pos, std::pair<int, int> &param);
    void scheduleInstructionBack(int pos, std::pair<int, int> &param);

    void display(std::ostream &out = std::cout);
    void displayNextInstruction(std::ostream &out = std::cout);
    
    int getFitness();
    int getSize();
    std::vector<std::string> getInstructions();
};