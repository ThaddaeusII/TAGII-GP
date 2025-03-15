#include "Program.h"

#include <iostream>

#include "MoveForward.h"
#include "LookForward.h"
#include "TurnLeft.h"
#include "TurnRight.h"

Program::Program()
{
    instructions.push_back(std::make_unique<MoveForward>());
    instructions.push_back(std::make_unique<TurnLeft>());
    instructions.push_back(std::make_unique<TurnRight>());
    instructions.push_back(std::make_unique<LookForward>());
    instructions.push_back(std::make_unique<MoveForward>());
}

void Program::execute(std::unique_ptr<Environment> &env)
{
}

void Program::display()
{
    int line = 1;
    for (auto &i : instructions)
    {
        std::cout << line << ": ";
        i->display();
        line++;
    }
}
