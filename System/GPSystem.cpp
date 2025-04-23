#include "GPSystem.h"

#include <iostream>

#include "SantaFeEnvironment.h"
#include "PacmanEnvironment.h"
#include "TournamentSelection.h"
#include "DefaultMutation.h"
#include "DefaultCrossover.h"

void GPSystem::initializePopulation()
{
    for (int i = 0; i < populationSize; ++i)
    {
        std::unique_ptr<Program> p = std::make_unique<Program>(environment);
        p->initialize(maxInstructions);
        population.push_back(std::move(p));
    }
}

void GPSystem::evaluateFitness()
{
    for (auto &p : population)
    {
        p->execute();
    }
}

GPSystem::GPSystem()
{
    // Default general parameters
    populationSize = 100;
    generations = 1000;
    mutationRate = 0.25;
    crossoverRate = 0.75;
    maxInstructions = 10;

    // Defualt environment
    environment = std::make_shared<PacmanEnvironment>("Pacman");
    environment->load("./Environments/pacman.env");
    environment->setMaxSteps(200);

    // Default genetic operators
    selector = std::make_shared<TournamentSelection>("Tournament Selection (size 7)");
    crossover = std::make_shared<DefaultCrossover>(crossoverRate, "One-Point Crossover (max copy of 10)");
    mutator = std::make_shared<DefaultMutation>(mutationRate, "Random Uniform Mutation");

    // Initialize the population
    initializePopulation();
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

void GPSystem::reset()
{
    // Clear population, then reinitialize randomly
    population.clear();
    initializePopulation();
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

void GPSystem::displayParameters()
{
    std::cout << std::endl << "==== System Parameters ====" << std::endl;
    std::cout << "General Parameters:" << std::endl;
    std::cout << "1. Population Size: " << populationSize << std::endl;
    std::cout << "2. Generations: " <<  generations << std::endl;
    std::cout << "3. Mutation Rate: " <<  mutationRate << std::endl;
    std::cout << "4. Crossover Rate: " <<  crossoverRate << std::endl;
    std::cout << "5. Max Initial Instructions: " <<  maxInstructions << std::endl;
    std::cout << "6. Max Program Steps: " << environment->getMaxSteps() << std::endl;
    std::cout << std::endl;
    std::cout << "Genetic Operations:" << std::endl;
    std::cout << "7. Selection Method: " <<  selector->getName() << std::endl;
    std::cout << "8. Mutation Method: " <<  mutator->getName() << std::endl;
    std::cout << "9. Crossover Method: " <<  crossover->getName() << std::endl;
    std::cout << std::endl;
    std::cout << "10. Environment: " << environment->getName() << std::endl;
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

void GPSystem::visualizeProgram(int idx)
{
    population[idx]->visualize();
}
