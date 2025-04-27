#include "TournamentSelectionElitism.h"

#include <algorithm>

#include "RandomGenerator.h"

int TournamentSelectionElitism::selectParent(std::vector<std::unique_ptr<Program>> &population)
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

TournamentSelectionElitism::TournamentSelectionElitism(std::string name) : Selection(name)
{
    tournamentSize = 7;
}

void TournamentSelectionElitism::select(std::vector<std::unique_ptr<Program>> &population,
    std::vector<std::unique_ptr<Program>> &children,
    std::shared_ptr<Mutation> &mutator,
    std::shared_ptr<Crossover> &crossover)
{
    children.clear();

    // Find and copy best program
    int best = 0;
    for (size_t i = 1; i < population.size(); ++i)
    {
        if (population[i]->getFitness() > population[best]->getFitness())
            best = i;
    }
    auto bestCopy = std::make_unique<Program>(getEnv(population[best]));
    auto &instr = getInstructions(population[best]);
    for (size_t i = 0; i < instr.size(); ++i)
        copyInstruction(bestCopy, instr[i]);
    children.push_back(std::move(bestCopy));

    while (children.size() < population.size())
    {
        int p1 = selectParent(population);
        int p2 = selectParent(population);

        std::unique_ptr<Program> child = crossover->cross(population[p1], population[p2]);
        mutator->mutate(child);

        children.push_back(std::move(child));
    }
}