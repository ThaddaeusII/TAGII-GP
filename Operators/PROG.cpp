#include "PROG.h"

#include <iostream>

#include "Program.h"
#include "Environment.h"
#include "RandomGenerator.h"

void PROG::execute(Program &prg, int pos, std::vector<std::pair<int, int>> &params)
{
    // Param -> (Param type, reference #)
    for (auto &p : params)
    {
        // Execute ControlOperator
        if (p.first)
        {
            prg.executeControl(pos, p.second);
        }
        
        // Execute TerminalOperator
        else
        {
            prg.executeTerminal(p.second);
        }
    }
}

void PROG::display()
{
    std::cout << "PROG" << x;
}

void PROG::randomize(std::vector<std::pair<int, int>> &params)
{
    int cSize = env.getControlOperators().size();
    int tSize = env.getTerminalOperators().size();

    auto &random = RandomGenerator::get();

    params.clear();
    for (int i = 0; i < x; ++i)
    {
        if (random.P(0.5))
            params.push_back(std::make_pair<int, int>(1, random.GetInt(0, cSize)));
        else
            params.push_back(std::make_pair<int, int>(0, random.GetInt(0, tSize)));
    }
}

void PROG::mutate(std::vector<std::pair<int, int>> &params)
{
    randomize(params);
}
