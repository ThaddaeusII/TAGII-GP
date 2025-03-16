#include "Environment.h"

#include <iostream>
#include <fstream>
#include <sstream>

Environment::Environment()
{
}

void Environment::move()
{

    if (forward(agentX, agentY))
    {
        food++;
        grid[agentY][agentX] = '-';
    }
}

bool Environment::forward(int &x, int &y)
{
    switch(agentDir)
    {
        case 0: // UP
            if (y > 0)
                y--;
            break;
        case 1: // Left
            if (x > 0)
                x--;
            break;
        case 2: // Down
            if (y < sizeY - 1)
                y++;
            break;
        case 3: // Right
            if (x < sizeX - 1)
                x++;
            break;
    }
    if (grid[y][x] == '1')
        return true;
    return false;
}

void Environment::load(std::string filepath)
{
    std::ifstream file(filepath);

    if (file.is_open())
    {
        std::string line;
        int row = -1;
        while (std::getline(file, line))
        {
            std::stringstream buffer(line);
            if (row == -1)
            {
                buffer >> sizeX >> sizeY >> startY >> startX >> startDir;
                agentX = startX;
                agentY = startY;
                agentDir = startDir;
                grid = std::vector(sizeY, std::vector<char>(sizeX, ' '));
                row++;
                continue;
            }

            int col = 0;
            while (buffer >> grid[row][col])
            {
                if (grid[row][col] == '1')
                    maxFood++;
                col++;
            } 
            row++;
        }
        file.close();
    } 
    else
    {
        std::cerr << "Unable to open environment file file: " << filepath << std::endl;
    }
}

void Environment::reset()
{
    agentX = startX;
    agentY = startY;
    agentDir = startDir;
    food = 0;
    for (int j = 0; j < sizeY; ++j)
        for (int i = 0; i < sizeX; ++i)
            if (grid[j][i] == '-')
                grid[j][i] = '1';
}

bool Environment::look(int n)
{
    bool found = false;
    int x = agentX;
    int y = agentY;
    for (int i = 0; i < n; ++ i)
        found = found || forward(x, y);
    return found;
}

void Environment::display()
{
    std::cout << "Food: " << food << "/" << maxFood << std::endl;
    for (int j = 0; j < sizeY; ++j)
    {
        for (int i = 0; i < sizeX; ++i)
        {
            if (i == agentX && j == agentY)
                switch(agentDir)
                {
                    case 0: // UP
                        std::cout << "^";
                        break;
                    case 1: // Left
                        std::cout << "<";
                        break;
                    case 2: // Down
                        std::cout << "v";
                        break;
                    case 3: // Right
                        std::cout << ">";
                        break;
                }
            else
                std::cout << grid[j][i];
        }
        std::cout << std::endl;
    }
}
