#pragma once

#include <vector>
#include <memory>

#include "ControlOperator.h"
#include "Environment.h"

class Crossover;
class Mutation;

class Program
{
private:
    struct Instruction
    {
        int reference;
        std::shared_ptr<ControlOperator> op;
        std::vector<std::pair<int, int>> params;

        Instruction(int count);
    };

    int fitness;
    int steps;
    std::vector<std::unique_ptr<Instruction>> instructions;
    std::shared_ptr<Environment> env;

    friend class Crossover;
    friend class Mutation;

public:
    Program(std::shared_ptr<Environment> env);
    void initialize(int numInstructions);
    void maxSteps(int steps);
    void executeControl(int pos, int ref = -1);
    void executeTerminal(int op);
    void evaluateFitness();
    void display();

    int getFitness();
    int getSteps();
    int getSize();
};