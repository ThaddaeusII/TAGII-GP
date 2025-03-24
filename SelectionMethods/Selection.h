#pragma once

#include <vector>
#include "Program.h"
#include "Mutation.h"
#include "Crossover.h"

class Selection
{
private:

public:
    virtual void select(std::vector<std::unique_ptr<Program>> &population,
        std::vector<std::unique_ptr<Program>> &children,
        std::shared_ptr<Mutation> &mutator,
        std::shared_ptr<Crossover> &crossover
    ) = 0;
};