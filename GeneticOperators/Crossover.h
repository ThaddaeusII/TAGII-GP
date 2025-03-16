#pragma once

#include "Program.h"
#include "OperatorRegistry.h"

class Crossover
{
private:

public:
    virtual ~Crossover() = default;
    virtual std::unique_ptr<Program> Cross(std::unique_ptr<Program>& program1, std::unique_ptr<Program>& program2, std::shared_ptr<Environment> &environment) = 0;
};