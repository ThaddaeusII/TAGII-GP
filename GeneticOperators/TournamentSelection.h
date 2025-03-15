#pragma once

#include "Selection.h"

class TournamentSelection : public Selection
{
private:

public:
    TournamentSelection();
    void Select(std::vector<std::unique_ptr<Program>> &population,
        std::vector<std::unique_ptr<Program>> &parents) override;
};