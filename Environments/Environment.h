#pragma once

#include <vector>
#include <string>

struct Environment
{
    std::vector<std::vector<char>> grid;
    int agentX, agentY, agentDir, 
        startX, startY, startDir,
        sizeX, sizeY, food, maxFood;

    Environment();
    void move();
    bool forward(int &x, int &y);
    void load(std::string filepath);
    void reset();
    bool look(int n);
    void display();
};