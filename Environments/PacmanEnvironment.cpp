#include "PacmanEnvironment.h"

#include <iostream>
#include <fstream>
#include <sstream>

// Control Operators
#include "PROG.h"
#include "LOOK_AHEAD.h"

// Terminal Operators
#include "Move.h"
#include "Turn.h"

void PacmanEnvironment::step()
{
    // Decrease power time if active
    if (poweredUp)
    {
        powerTimer--;
        if (powerTimer <= 0)
        {
            poweredUp = false;
            powerTimer = 0;
        }
    }

    // Update ghosts
    updateGhosts();

    curSteps--;
}

void PacmanEnvironment::move()
{
    // Check out of bounds
    int newX = agentX, newY = agentY;
    if (!peekForward(newX, newY))
    {
        step();
        return;
    }

    // Wall check
    if (grid[newY][newX] == '#')
    {
        step();
        return;
    }

    // Move agent
    agentX = newX;
    agentY = newY;

    // Check if ghosts hit
    checkHit();

    // Pellet collection
    if (grid[agentY][agentX] == '.')
    {
        fitness++;
        grid[agentY][agentX] = ' ';
    }
    else if (grid[agentY][agentX] == 'O') // Power pellet
    {
        fitness += 5;
        poweredUp = true;
        powerTimer = 11; // last for 10 moves (11 including this step)
        grid[agentY][agentX] = ' ';
    }

    // Game step has passed, update ghosts and powerup timer
    step();
}

void PacmanEnvironment::turnLeft()
{
    agentDir = (agentDir + 1) % 4;
    step();
}

void PacmanEnvironment::turnRight()
{
    agentDir = (agentDir + 3) % 4;
    step();
}

bool PacmanEnvironment::peekForward(int &x, int &y)
{
    switch(agentDir)
    {
        case 0: if (y > 0) { y--; return true; } break;         // UP
        case 1: if (x > 0) { x--; return true; } break;         // LEFT
        case 2: if (y < sizeY - 1) { y++; return true; } break; // DOWN
        case 3: if (x < sizeX - 1) { x++; return true; } break; // RIGHT
    }
    return false; // hit boundary
}

bool PacmanEnvironment::pelletAhead()
{
    int x = agentX, y = agentY;
    while (true)
    {
        if (!peekForward(x, y))
            return false;
        if (grid[y][x] == '#')
            return false;
        if (grid[y][x] == '.' || grid[y][x] == 'O')
            return true;
    }
}

bool PacmanEnvironment::ghostAhead()
{
    int x = agentX, y = agentY;
    while (true)
    {
        if (!peekForward(x, y))
            return false;
        if (grid[y][x] == '#')
            return false;
        for (auto& ghost : ghosts)
        {
            if (ghost.x == x && ghost.y == y)
                return true;
        }
    }
}

bool PacmanEnvironment::superPelletAhead()
{
    int x = agentX, y = agentY;
    while (true)
    {
        if (!peekForward(x, y))
            return false;
        if (grid[y][x] == '#')
            return false;
        if (grid[y][x] == 'O')
            return true;
    }
}

void PacmanEnvironment::updateGhosts()
{
    // Simple ghost AI: each ghost moves randomly or in a fixed pattern
    for (auto& ghost : ghosts)
    {
        int dx[] = {0, -1, 0, 1};
        int dy[] = {-1, 0, 1, 0};

        int dir = ghost.dir;
        int nx = ghost.x + dx[dir];
        int ny = ghost.y + dy[dir];

        if (nx >= 0 && ny >= 0 && nx < sizeX && ny < sizeY && grid[ny][nx] != '#')
        {
            ghost.x = nx;
            ghost.y = ny;
        }
        else
        {
            ghost.dir = (ghost.dir + 1) % 4; // change direction if blocked
        }
    }

    checkHit();
}

void PacmanEnvironment::checkHit()
{
    // Check if ghost hits pacman
    for (auto& ghost : ghosts)
    {
        if (ghost.x == agentX && ghost.y == agentY)
        {
            if (poweredUp)
            {
                // "Eat" ghost, removing it
                ghost.x = -1;
                ghost.y = -1;
                fitness += 10;
            }
            else
            {
                // Death
                fitness = -100;
                curSteps = 0;
                return;
            }
        }
    }
}

PacmanEnvironment::PacmanEnvironment(std::string name) : Environment(name)
{
    registerAllOperators();
}

void PacmanEnvironment::registerAllOperators()
{
    // Control Operators
    registerControlOperator(std::make_shared<PROG>(*this, 2));
    registerControlOperator(std::make_shared<PROG>(*this, 3));
    registerControlOperator(std::make_shared<PROG>(*this, 4));
    registerControlOperator(std::make_shared<PROG>(*this, 5));
    registerControlOperator(std::make_shared<LOOK_AHEAD>(*this, [this](){ return this->pelletAhead(); }, "LOOK_PELLET"));
    registerControlOperator(std::make_shared<LOOK_AHEAD>(*this, [this](){ return this->superPelletAhead(); }, "LOOK_SUPER_PELLET"));
    registerControlOperator(std::make_shared<LOOK_AHEAD>(*this, [this](){ return this->ghostAhead(); }, "LOOK_GHOST"));

    // Terminal Operators
    registerTerminalOperator(std::make_shared<Move>(*this, [this](){ this->move(); }));
    registerTerminalOperator(std::make_shared<Turn>(*this, [this](){ this->turnLeft(); }, true));
    registerTerminalOperator(std::make_shared<Turn>(*this, [this](){ this->turnRight(); }, false));
}

void PacmanEnvironment::reset()
{
    agentX = startX;
    agentY = startY;
    agentDir = startDir;
    poweredUp = false;
    powerTimer = 0;
    fitness = 0;
    curSteps = maxSteps;

    grid = initialGrid;
    for (auto& ghost : ghosts)
    {
        ghost.x = ghost.startX;
        ghost.y = ghost.startY;
    }

    // Check if pacman starts on pellet
    if (grid[agentY][agentX] == '.')
    {
        fitness++;
        grid[agentY][agentX] = ' ';
    }
    else if (grid[agentY][agentX] == 'O') // Power pellet
    {
        fitness += 5;
        poweredUp = true;
        powerTimer = 10; // last for 10 moves
        grid[agentY][agentX] = ' ';
    }
}

void PacmanEnvironment::load(std::string envPath)
{
    std::ifstream file(envPath);
    if (file.is_open())
    {
        std::string line;
        std::string label;
        int ghostCount = 0;
        maxFitness = 0;

        // GridSize
        std::getline(file, line);
        std::stringstream ssGridSize(line);
        ssGridSize >> label >> sizeX >> label >> sizeY;

        // AgentXYDir
        std::getline(file, line);
        std::stringstream ssAgentXYDir(line);
        ssAgentXYDir >> label >> startX >> label >> startY >> label >> startDir;

        // Ghosts count
        std::getline(file, line);
        std::stringstream ssGhosts(line);
        ssGhosts >> label >> ghostCount;
        maxFitness += ghostCount * 10;

        // GhostXY entries
        ghosts.clear();
        for (int i = 0; i < ghostCount; ++i)
        {
            std::getline(file, line);
            std::stringstream ssGhost(line);
            int gx, gy;
            ssGhost >> label >> gx >> label >> gy;
            ghosts.push_back({gx, gy, gx, gy, 0});
        }

        // Skip "Grid:"
        std::getline(file, line);

        // Load the grid
        grid = std::vector(sizeY, std::vector<char>(sizeX, ' '));

        for (int row = 0; row < sizeY; ++row)
        {
            std::getline(file, line);
            std::stringstream ssGrid(line);
            for (int col = 0; col < sizeX; ++col)
            {
                ssGrid >> grid[row][col];
                if (grid[row][col] == '.') maxFitness++;
                if (grid[row][col] == 'O') maxFitness += 5;
            }
        }

        file.close();
        initialGrid = grid;
    }
    else
    {
        std::cerr << "Unable to open environment file: " << envPath << std::endl;
    }
}

void PacmanEnvironment::display()
{
    std::cout << "Score: " << fitness << " / " << maxFitness;
    std::cout << " (Powered: " << powerTimer << ")";
    std::cout << std::endl;

    for (int j = 0; j < sizeY; ++j)
    {
        for (int i = 0; i < sizeX; ++i)
        {
            if (i == agentX && j == agentY)
            {
                switch (agentDir)
                {
                    case 0: std::cout << "^"; break;
                    case 1: std::cout << "<"; break;
                    case 2: std::cout << "v"; break;
                    case 3: std::cout << ">"; break;
                }
            }
            else
            {
                bool ghostHere = false;
                for (auto& g : ghosts)
                {
                    if (g.x == i && g.y == j)
                    {
                        ghostHere = true;
                        break;
                    }
                }

                if (ghostHere)
                    std::cout << "G";
                else
                    std::cout << grid[j][i];
            }
        }
        std::cout << std::endl;
    }
}
