#pragma once

#include "Environment.h"

class Instruction
{
private:

public:
    virtual ~Instruction() = default;
    virtual void execute(Environment& env) = 0;
    virtual void display() = 0;
};