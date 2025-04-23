#pragma once

#include <vector>
#include <memory>

#include "Environment.h"
#include "ControlOperator.h"

class Crossover;
class Mutation;

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

    void getInput();

    friend class Crossover;
    friend class Mutation;

public:
    Program(std::shared_ptr<Environment> env);
    void initialize(int numInstructions);
    void execute();
    void executeControl(int pos, int ref = -1);
    void executeTerminal(int op);
    void visualize();
    void visualizeControl(int pos, int ref = -1);
    void visualizeTerminal(int op);
    void evaluateFitness();
    void display();

    int getFitness();
    int getSize();
};