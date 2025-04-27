#pragma once

#include "Selection.h"

class TournamentSelectionElitism : public Selection
{
private:
    int tournamentSize;
    int elitismSize;
    int selectParent(std::vector<std::unique_ptr<Program>> &population);

public:
    TournamentSelectionElitism(std::string name);
    void select(std::vector<std::unique_ptr<Program>> &population,
        std::vector<std::unique_ptr<Program>> &children,
        std::shared_ptr<Mutation> &mutator,
        std::shared_ptr<Crossover> &crossover
    ) override;
};