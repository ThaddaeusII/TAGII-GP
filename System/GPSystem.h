#pragma once

#include<vector>
#include <memory>

#include "Program.h"
#include "Environment.h"
#include "Selection.h"
#include "Mutation.h"
#include "Crossover.h"

class GPSystem
{
private:
    size_t populationSize;
    size_t generations;
    double mutationRate;

    std::vector<std::unique_ptr<Program>> population;
    std::unique_ptr<Environment> environment;
    std::unique_ptr<Selection> selector;
    std::unique_ptr<Mutation> mutator;
    std::unique_ptr<Crossover> crossover;

    void initializePopulation();
    void evaluateFitness();
    void evolve();

public:
    GPSystem();
    void run(size_t populationSize,
        size_t generations,
        double mutationRate);
    void display();
};