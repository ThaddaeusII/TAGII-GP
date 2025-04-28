#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Program.h"
#include "Environment.h"
#include "Selection.h"
#include "Mutation.h"
#include "Crossover.h"

class GPSystem
{
public:
    struct GPStats
    {
        double avgFitness;
        int bestFitness;
        int bestProgram;
        double avgProgramSize;
        int smallestProgramSize;
        int largestProgramSize;

        void display(std::ostream& out);
    };

private:
    int populationSize;
    int generations;
    double mutationRate;
    double crossoverRate;
    int maxInstructions;

    GPStats curStats;

    std::vector<std::unique_ptr<Program>> population;
    std::shared_ptr<Selection> selector;
    std::shared_ptr<Mutation> mutator;
    std::shared_ptr<Crossover> crossover;
    std::shared_ptr<Environment> environment;

    void initializePopulation();

public:
    GPSystem();
    void evolve();
    void step();
    void reset();
    void calcStats();
    void evaluateFitness();

    void displayProgram(int idx);
    void displayAllPrograms();
    void displayParameters();
    void displayStats();
    void displayEnvironment(std::ostream &out = std::cout);

    std::vector<std::string> getProgramInststructions(int idx);
    int getProgramFitness(int idx) { return population[idx]->getFitness(); }
    int getProgramSize(int idx) { return population[idx]->getSize(); }
    Program* getProgram(int idx) { return population[idx].get(); }

    GPStats getStats() { return curStats; }

    void setPopulationSize(int size) { populationSize = size; }
    void setGenerations(int gens) { generations = gens; }
    void setMutationRate(double rate) { mutationRate = rate; }
    void setCrossoverRate(double rate) { crossoverRate = rate; }
    void setMaxInstructions(int max) { maxInstructions = max; }
    void setMaxSteps(int steps) { environment->setMaxSteps(steps); }

    int getPopulationSize() { return populationSize; }
    int getGenerations() { return generations; }
    double getMutationRate() { return mutationRate; }
    double getCrossoverRate() { return crossoverRate; }
    int getMaxInstructions() { return maxInstructions; }
    int getCurSteps() { return environment->getCurSteps(); }
    int getMaxSteps() { return environment->getMaxSteps(); }

    void setSelectionMethod(std::shared_ptr<Selection> s) { selector = s; }
    void setMutationMethod(std::shared_ptr<Mutation> m) { mutator = m; }
    void setCrossoverMethod(std::shared_ptr<Crossover> c) { crossover = c; }

    void SetEnvironment(std::shared_ptr<Environment> e) { environment = e; }
};