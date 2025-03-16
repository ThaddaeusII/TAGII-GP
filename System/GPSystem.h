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
    int numInstructions;
    int steps;

    std::vector<std::unique_ptr<Program>> population;
    std::unique_ptr<Selection> selector;
    std::unique_ptr<Mutation> mutator;
    std::unique_ptr<Crossover> crossover;
    std::shared_ptr<Environment> environment;

    void initializePopulation();
    void evaluateFitness();
    void evolve();

public:
    GPSystem();
    void run(
        size_t populationSize,
        size_t generations,
        double mutationRate,
        int numInstructions,
        int steps,
        std::string envPath
    );
    void displayPrograms();
    void displayEnvironment();
};