#include "GPSystem.h"

#include <iostream>

#include "TournamentSelection.h"
#include "DefaultMutation.h"
#include "DefaultCrossover.h"
#include "RandomGenerator.h"

void GPSystem::initializePopulation()
{
    for (int i = 0; i < populationSize; ++i)
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
    std::vector<std::unique_ptr<Program>> children;

    // Evaluate initial generation's fitness
    evaluateFitness();

    for (int gen = 0; gen < generations; ++gen)
    {
        // Select next generation using provided selector, mutator, and crossover objects
        selector->select(population, children, mutator, crossover);

        // Set population to next generation and evaluate fitness
        std::swap(population, children); // @TAG: Efficiency?
        evaluateFitness();

        std::cout << "Generation " << gen << ":" << std::endl;
        displayStats();
        std::cout << std::endl;
    }
}

GPSystem::GPSystem()
{
}

void GPSystem::run(size_t populationSize,
    size_t generations,
    double crossoverRate,
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
    selector = std::make_shared<TournamentSelection>();
    crossover = std::make_shared<DefaultCrossover>(crossoverRate);
    mutator = std::make_shared<DefaultMutation>(mutationRate);

    // Initialize the population
    initializePopulation();
    std::cout << "---------- Initial Programs ----------" << std::endl << std::endl;
    displayPrograms();
    
    // Evolve the population
    std::cout << "---------- Generations ----------" << std::endl << std::endl;
    evolve();

    std::cout << "---------- Final Programs ----------" << std::endl << std::endl;
    displayPrograms();
    displayStats();
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
