#pragma once

#include <vector>
#include <memory>

#include "Instruction.h"
#include "Environment.h"

class Program
{
private:
    std::vector<std::unique_ptr<Instruction>> instructions;
    int fitness;

public:
    Program();
    void execute(std::unique_ptr<Environment> &env);
    void display();
};