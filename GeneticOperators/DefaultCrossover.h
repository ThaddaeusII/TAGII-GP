#pragma once

#include "Crossover.h"

class DefaultCrossover : public Crossover
{
private:

public:
    virtual ~DefaultCrossover() = default;
    std::unique_ptr<Program> Cross(std::unique_ptr<Program>& program1, std::unique_ptr<Program>& program2, std::shared_ptr<Environment> &environment) override;
};