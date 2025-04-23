#pragma once

#include <vector>
#include <string>
#include "Program.h"
#include "Mutation.h"
#include "Crossover.h"

class Selection
{
private:
    std::string name;

public:
    Selection(std::string name) : name(name) {}
    std::string getName() { return name; }
    virtual void select(std::vector<std::unique_ptr<Program>> &population,
        std::vector<std::unique_ptr<Program>> &children,
        std::shared_ptr<Mutation> &mutator,
        std::shared_ptr<Crossover> &crossover
    ) = 0;
};