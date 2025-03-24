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
    int populationSize = 100;
    int generations = 200;
    double mutationRate = 0.25;
    double crossoverRate = 0.75;
    int maxInstructions = 10;
    int maxSteps = 400;

    std::vector<std::unique_ptr<Program>> population;
    std::shared_ptr<Selection> selector;
    std::shared_ptr<Mutation> mutator;
    std::shared_ptr<Crossover> crossover;
    std::shared_ptr<Environment> environment;

    void initializePopulation();
    void evaluateFitness();
    void evolve();

public:
    GPSystem();
    void run();

    void displayProgram(int idx);
    void displayAllPrograms();
    void displayStats();
    void displayEnvironment();
};