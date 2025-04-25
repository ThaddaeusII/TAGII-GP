#pragma once

#include "Crossover.h"

class DefaultCrossover : public Crossover
{
private:
    int maxCopySize = 10;

public:
    DefaultCrossover(double crossoverRate, std::string name) : Crossover(crossoverRate, name) {}
    std::unique_ptr<Program> cross(std::unique_ptr<Program>& program1, std::unique_ptr<Program>& program2);
};