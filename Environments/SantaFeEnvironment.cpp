#include "SantaFeEnvironment.h"

#include <iostream>
#include <fstream>
#include <sstream>

// Control Operators
#include "PROG.h"
#include "LOOK.h"

// Terminal Operators
#include "Move.h"
#include "Turn.h"

SantaFeEnvironment::SantaFeEnvironment(std::string name) : Environment(name)
{
    registerAllOperators();
}

void SantaFeEnvironment::registerAllOperators()
{
    // Control Operators
    registerControlOperator(std::make_shared<PROG>(*this, 2));
    registerControlOperator(std::make_shared<PROG>(*this, 3));
    registerControlOperator(std::make_shared<LOOK>(*this, std::bind(&SantaFeEnvironment::look, this, 1)));

    // Terminal Operators
    registerTerminalOperator(std::make_shared<Move>(*this, std::bind(&SantaFeEnvironment::move, this)));
    registerTerminalOperator(std::make_shared<Turn>(*this, std::bind(&SantaFeEnvironment::turnLeft, this), true));
    registerTerminalOperator(std::make_shared<Turn>(*this, std::bind(&SantaFeEnvironment::turnRight, this), false));
}

void SantaFeEnvironment::reset()
{
    agentX = startX;
    agentY = startY;
    agentDir = startDir;
    fitness = 0;
    for (int j = 0; j < sizeY; ++j)
        for (int i = 0; i < sizeX; ++i)
            if (grid[j][i] == '-')
                grid[j][i] = '1';
}

void SantaFeEnvironment::load(std::string envPath)
{
    std::ifstream file(envPath);

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
        std::cerr << "Unable to open environment file file: " << envPath << std::endl;
    }
}

void SantaFeEnvironment::display(std::ostream &out)
{
    out << "Food: " << fitness << "/" << maxFood << std::endl;
    for (int j = 0; j < sizeY; ++j)
    {
        for (int i = 0; i < sizeX; ++i)
        {
            if (i == agentX && j == agentY)
                switch(agentDir)
                {
                    case 0: // UP
                        out << "^";
                        break;
                    case 1: // Left
                        out << "<";
                        break;
                    case 2: // Down
                        out << "v";
                        break;
                    case 3: // Right
                        out << ">";
                        break;
                }
            else
                out << grid[j][i];
        }
        out << std::endl;
    }
}

void SantaFeEnvironment::move()
{

    if (forward(agentX, agentY))
    {
        fitness++;
        grid[agentY][agentX] = '-';
    }
}

void SantaFeEnvironment::turnLeft()
{
    agentDir += 1;
    agentDir %= 4;
}

void SantaFeEnvironment::turnRight()
{
    agentDir -= 1;
    agentDir %= 4;
}

bool SantaFeEnvironment::forward(int &x, int &y)
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

bool SantaFeEnvironment::look(int n)
{
    bool found = false;
    int x = agentX;
    int y = agentY;
    for (int i = 0; i < n; ++ i)
        found = found || forward(x, y);
    return found;
}