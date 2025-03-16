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
    int populationSize;
    int generations;
    double mutationRate;
    int numInstructions;
    int steps;

    std::vector<std::unique_ptr<Program>> population;
    std::shared_ptr<Selection> selector;
    std::shared_ptr<Mutation> mutator;
    std::shared_ptr<Crossover> crossover;
    std::shared_ptr<Environment> environment;

    void initializePopulation();
    void evaluateFitness();
    void evolve();
    void displayPrograms();
    void displayEnvironment();
    void displayStats();

public:
    GPSystem();
    void run(
        size_t populationSize,
        size_t generations,
        double crossoverRate,
        double mutationRate,
        int numInstructions,
        int steps,
        std::string envPath
    );
};