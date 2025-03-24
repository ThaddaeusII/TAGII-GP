#include "GPSystem.h"

#include <iostream>

#include "SantaFeEnvironment.h"
#include "TournamentSelection.h"
#include "DefaultMutation.h"
#include "DefaultCrossover.h"

void GPSystem::initializePopulation()
{
    for (int i = 0; i < populationSize; ++i)
    {
        std::unique_ptr<Program> p = std::make_unique<Program>(environment);
        p->initialize(maxInstructions);
        //p->initPerfect();
        population.push_back(std::move(p));
    }
}

void GPSystem::evaluateFitness()
{
    for (auto &p : population)
    {
        environment->reset();
        p->setSteps(maxSteps);
        while (p->getSteps() > 0)
        {
            p->executeControl(0);
        }
        p->evaluateFitness();
    }
}

void GPSystem::evolve()
{
    std::vector<std::unique_ptr<Program>> children;

    // Evaluate initial generation's fitness
    evaluateFitness();

    for (int gen = 0; gen < generations; ++gen)
    {
        // Select next generation using provided selector, mutator, and crossover objects
        selector->select(population, children, mutator, crossover);

        // Set population to next generation and evaluate fitness
        std::swap(population, children);
        evaluateFitness();
    }
}

GPSystem::GPSystem()
{
}

void GPSystem::run()
{
    // Setup environment
    environment = std::make_shared<SantaFeEnvironment>();
    environment->load("./Environments/santafe.env");
    displayEnvironment();

    // Setup genetic operators
    selector = std::make_shared<TournamentSelection>();
    crossover = std::make_shared<DefaultCrossover>(crossoverRate);
    mutator = std::make_shared<DefaultMutation>(mutationRate);

    // Initialize the population
    initializePopulation();
    displayAllPrograms();
    
    // Evolve the population
    evolve();
    displayAllPrograms();
    displayStats();
}

void GPSystem::displayProgram(int idx)
{
    std::cout << "Program " << idx+1 << " -> Fitness: " << population[idx]->getFitness() << std::endl;
    population[idx]->display();
    std::cout << std::endl;
}

void GPSystem::displayAllPrograms()
{
    for (size_t i = 0; i < population.size(); ++i)
    {
        displayProgram(i);
    }
}

void GPSystem::displayStats()
{
    double avgFitness = 0;
    int bestFitness = -1;
    int bestProgram = -1;
    double avgProgramSize = 0;
    int smallestProgramSize = INT_MAX;
    int largestProgramSize = -1;

    for (int i = 0; i < populationSize; ++i)
    {
        int f = population[i]->getFitness();
        avgFitness += f;
        if (f > bestFitness)
        {
            bestFitness = f;
            bestProgram = i;
        }

        int s = population[i]->getSize();
        avgProgramSize += s;
        if (s < smallestProgramSize)
            smallestProgramSize = s;
        if (s > largestProgramSize)
            largestProgramSize = s;
    }
    avgFitness /= populationSize;
    avgProgramSize /= populationSize;

    std::cout << "Population size: " << population.size() << std::endl;
    std::cout << "Best fitness:    " << bestFitness << std::endl;
    std::cout << "Best program:    " << bestProgram << std::endl;
    std::cout << "Avg fitness:     " << avgFitness << std::endl;
    std::cout << "Minimum length:  " << smallestProgramSize << std::endl;
    std::cout << "Maximum length:  " << largestProgramSize << std::endl;
    std::cout << "Avg length:      " << avgProgramSize << std::endl;

}

void GPSystem::displayEnvironment()
{
    if (environment == nullptr)
        return;
    std::cout << "Environment:" << std::endl;
    environment->display();
}
