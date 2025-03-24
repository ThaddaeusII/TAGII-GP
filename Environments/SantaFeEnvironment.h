#pragma once

#include "Environment.h"

#include <vector>

class SantaFeEnvironment : public Environment
{
private:
    std::vector<std::vector<char>> grid;
    int agentX, agentY, agentDir, 
        startX, startY, startDir,
        sizeX, sizeY, maxFood;

    
    void move();
    void turnLeft();
    void turnRight();
    bool forward(int &x, int &y);
    bool look(int n);

public:
    SantaFeEnvironment();
    void registerAllOperators() override;
    void reset() override;
    void load(std::string envPath) override;
    void display() override;
};