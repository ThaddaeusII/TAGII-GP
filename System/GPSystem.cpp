#include "GPSystem.h"

#include <iostream>

#include "TournamentSelection.h"
#include "DefaultMutation.h"
#include "DefaultCrossover.h"
#include "RandomGenerator.h"

void GPSystem::initializePopulation()
{
    for (size_t i = 0; i < populationSize; ++i)
    {
        std::unique_ptr<Program> p = std::make_unique<Program>(environment);
        p->initialize(numInstructions);
        population.push_back(std::move(p));
    }
}

void GPSystem::evaluateFitness()
{
    for (auto &p : population)
    {
        environment->reset();
        p->maxSteps(steps);
        while (p->getSteps() > 0)
        {
            p->executeControl(0);
        }
        p->evaluateFitness();
    }
}

void GPSystem::evolve()
{
    std::vector<std::unique_ptr<Program>> parents;
    std::vector<std::unique_ptr<Program>> children;
    auto &random = RandomGenerator::get();

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
            std::unique_ptr<Program> child = crossover->Cross(parents[parent1], parents[parent2], environment);
            
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
    double mutationRate,
    int numInstructions,
    int steps,
    std::string envPath
)
{
    // Save parameters
    this->populationSize = populationSize;
    this->generations = generations;
    this->mutationRate = mutationRate;
    this->numInstructions = numInstructions;
    this->steps = steps;

    // Setup environment
    environment = std::make_shared<Environment>();
    environment->load(envPath);
    displayEnvironment();
    
    // Setup genetic operators
    selector = std::make_unique<TournamentSelection>();
    mutator = std::make_unique<DefaultMutation>();
    crossover = std::make_unique<DefaultCrossover>();

    // Initialize the population
    initializePopulation();
    std::cout << "---------- Initial Programs ----------" << std::endl << std::endl;
    displayPrograms();

    // Evolve the population
    evolve();
    std::cout << "---------- Final Programs ----------" << std::endl << std::endl;
    displayPrograms();
}

void GPSystem::displayEnvironment()
{
    if (environment == nullptr)
        return;
    std::cout << "Environment:" << std::endl;
    environment->display();
}

void GPSystem::displayPrograms()
{
    int num = 1;
    for (auto &p : population)
    {
        std::cout << "Program " << num << " -> Fitness: " << p->getFitness() << std::endl;
        p->display();
        std::cout << std::endl;
        num++;
    }
}
