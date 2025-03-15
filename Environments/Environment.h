#pragma once

#include <vector>

class Environment
{
    std::vector<std::vector<char>> grid;
    int agentX, agentY;

public:
    Environment();
    void reset();
    bool step(int action);
    void printState() const;
};