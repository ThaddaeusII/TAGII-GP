#pragma once

#include "Crossover.h"

class DefaultCrossover : public Crossover
{
private:
    int maxSize = 10;

public:
    DefaultCrossover(double crossoverRate): Crossover(crossoverRate) {}
    std::unique_ptr<Program> cross(std::unique_ptr<Program>& program1, std::unique_ptr<Program>& program2) override;
};