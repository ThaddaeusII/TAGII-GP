#pragma once

#include "Program.h"

class Mutation
{
private:

public:
    virtual ~Mutation() = default;
    virtual void Mutate(std::unique_ptr<Program> &program) = 0;
};