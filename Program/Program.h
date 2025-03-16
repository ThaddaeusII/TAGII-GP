#pragma once

#include <vector>
#include <memory>

#include "ControlOperator.h"
#include "Environment.h"

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

    std::vector<std::unique_ptr<Instruction>> instructions;
    std::shared_ptr<Environment> env;
    int fitness;
    int steps;

public:
    Program(std::shared_ptr<Environment> env);
    void initialize(int numInstructions);
    void maxSteps(int steps);
    void executeControl(int pos, int ref = -1);
    void executeTerminal(int op);
    void display();
    void evaluateFitness();
    int getFitness();
    int getSteps();
};