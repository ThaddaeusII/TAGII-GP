#pragma once

#include <vector>
#include "Program.h"

class Selection
{
private:

public:
    virtual ~Selection() = default;
    virtual void Select(std::vector<std::unique_ptr<Program>> &population,
        std::vector<std::unique_ptr<Program>> &parents) = 0;
};