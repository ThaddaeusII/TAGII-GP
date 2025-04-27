#pragma once

#include "Environment.h"

#include <vector>

class PacmanEnvironment : public Environment
{
private:
    struct Ghost
    {
        int x, y;
        int startX, startY;
        int dir;
        int startDir;
    };

    std::vector<std::vector<char>> initialGrid;
    std::vector<std::vector<char>> grid;
    std::vector<Ghost> ghosts;

    std::string envPath;

    int agentX, agentY, agentDir; 
    int startX, startY, startDir;
    int sizeX, sizeY;
    int maxFitness;
    bool poweredUp;
    int powerTimer;
    
    void step();
    void move();
    void turnLeft();
    void turnRight();
    bool peekForward(int &x, int &y);
    bool pelletAhead();
    bool ghostAhead();
    bool superPelletAhead();
    void updateGhosts();
    void checkHit();

public:
    PacmanEnvironment(std::string name);
    void registerAllOperators() override;
    void reset() override;
    void load(std::string envPath) override;
    void display(std::ostream &out = std::cout) override;
};