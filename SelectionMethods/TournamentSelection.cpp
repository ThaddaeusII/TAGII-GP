#include "TournamentSelection.h"

#include "RandomGenerator.h"

int TournamentSelection::selectParent(std::vector<std::unique_ptr<Program>> &population)
{
    auto &random = RandomGenerator::get();
    int parent = random.GetInt(0, population.size());

    for (int i = 0; i < tournamentSize; ++i)
    {
        int nextParent = random.GetInt(0, population.size());
        if (population[nextParent]->getFitness() > population[parent]->getFitness())
            parent = nextParent;
    }
    return parent;
}

TournamentSelection::TournamentSelection()
{
    tournamentSize = 7;
}

void TournamentSelection::select(std::vector<std::unique_ptr<Program>> &population, std::vector<std::unique_ptr<Program>> &children, std::shared_ptr<Mutation> &mutator, std::shared_ptr<Crossover> &crossover)
{
    children.clear();
    while (children.size() < population.size())
    {
        int p1 = selectParent(population);
        int p2 = selectParent(population);

        std::unique_ptr<Program> child = crossover->cross(population[p1], population[p2]);
        mutator->mutate(child);

        children.push_back(std::move(child));
    }
}