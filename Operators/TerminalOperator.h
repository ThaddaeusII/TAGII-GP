#pragma once

#include <memory>
#include "Environment.h"

class Program;

class TerminalOperator
{
private:

public:
    virtual void execute(std::shared_ptr<Environment> &env, int &steps) = 0;
    virtual void display() = 0;
};