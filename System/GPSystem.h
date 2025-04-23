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
    bool hasRun = false;

    int populationSize;
    int generations;
    double mutationRate;
    double crossoverRate;
    int maxInstructions;

    std::vector<std::unique_ptr<Program>> population;
    std::shared_ptr<Selection> selector;
    std::shared_ptr<Mutation> mutator;
    std::shared_ptr<Crossover> crossover;
    std::shared_ptr<Environment> environment;

    void initializePopulation();
    void evaluateFitness();

public:
    GPSystem();
    void evolve();
    void reset();

    void displayProgram(int idx);
    void displayAllPrograms();
    void displayParameters();
    void displayStats();
    void displayEnvironment();
    void visualizeProgram(int idx);

    void setPopulationSize(int size) { populationSize = size; }
    void setGenerations(int gens) { generations = gens; }
    void setMutationRate(double rate) { mutationRate = rate; }
    void setCrossoverRate(double rate) { crossoverRate = rate; }
    void setMaxInstructions(int max) { maxInstructions = max; }
    void setMaxSteps(int steps) { environment->setMaxSteps(steps); }

    double getMutationRate() { return mutationRate; }
    double getCrossoverRate() { return crossoverRate; }

    void setSelectionMethod(std::shared_ptr<Selection> s) { selector = s; }
    void setMutationMethod(std::shared_ptr<Mutation> m) { mutator = m; }
    void setCrossoverMethod(std::shared_ptr<Crossover> c) { crossover = c; }

    void SetEnvironment(std::shared_ptr<Environment> e) { environment = e; }
};