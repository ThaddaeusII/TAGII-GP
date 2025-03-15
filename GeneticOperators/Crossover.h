#pragma once

#include "Program.h"

class Crossover
{
private:

public:
    virtual ~Crossover() = default;
    virtual std::unique_ptr<Program> Cross(std::unique_ptr<Program>& program1, std::unique_ptr<Program>& program2) = 0;
};