#include "GPSystem.h"

#include <iostream>

#include "TournamentSelection.h"
#include "DefaultMutation.h"
#include "DefaultCrossover.h"
#include "emp/math/Random.hpp"

void GPSystem::initializePopulation()
{
    for (size_t i = 0; i < populationSize; ++i)
    {
        population.push_back(std::make_unique<Program>());
    }
}

void GPSystem::evaluateFitness()
{
    /* for (auto &p : population)
    {
        p->execute(environment);
    } */
}

void GPSystem::evolve()
{
    std::vector<std::unique_ptr<Program>> parents;
    std::vector<std::unique_ptr<Program>> children;
    emp::Random random;

    // Evaluate initial generation's fitness
    evaluateFitness();

    for (size_t gen = 0; gen < generations; ++gen)
    {
        // Select a set of parents to procreate
        parents.clear();
        selector->Select(population, parents);

        // Create next generation
        children.clear();
        while (children.size() < populationSize)
        {
            // Crossover two parents @TAG: Allows for repeats, need no replacement
            int parent1 = random.GetInt(0, parents.size());
            int parent2 = random.GetInt(0, parents.size());
            std::unique_ptr<Program> child = crossover->Cross(parents[parent1], parents[parent2]);
            
            // Mutate child with probability mutationRate
            if (random.P(mutationRate))
                mutator->Mutate(child);

            children.push_back(std::move(child));
        }

        // Set population to next generation and evaluate fitness
        std::swap(population, children); // @TAG: Efficiency?
        evaluateFitness();
    }
}

GPSystem::GPSystem()
{
}

void GPSystem::run(size_t populationSize,
    size_t generations,
    double mutationRate)
{
    // Save parameters
    this->populationSize = populationSize;
    this->generations = generations;
    this->mutationRate = mutationRate;
    
    // Setup genetic operators
    selector = std::make_unique<TournamentSelection>();
    mutator = std::make_unique<DefaultMutation>();
    crossover = std::make_unique<DefaultCrossover>();

    // Initialize the population
    initializePopulation();

    // Evolve the population
    evolve();
}

void GPSystem::display()
{
    int num = 1;
    for (auto &p : population)
    {
        std::cout << "Program " << num << ":" << std::endl;
        p->display();
        std::cout << std::endl;
        num++;
    }
}
