#include "LOOK.h"

#include <iostream>

#include "Program.h"
#include "Environment.h"
#include "RandomGenerator.h"

void LOOK::execute(Program &prg, int pos, std::vector<std::pair<int, int>> &params)
{
    if (lookFunction())
    {
        auto p = params[0];

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
    else
    {
        auto p = params[1];

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

void LOOK::visualize(Program &prg, int pos, std::vector<std::pair<int, int>> &params)
{
    if (lookFunction())
    {
        auto p = params[0];

        // Execute ControlOperator
        if (p.first)
        {
            prg.visualizeControl(pos, p.second);
        }
        
        // Execute TerminalOperator
        else
        {
            prg.visualizeTerminal(p.second);
        }
    }
    else
    {
        auto p = params[1];

        // Execute ControlOperator
        if (p.first)
        {
            prg.visualizeControl(pos, p.second);
        }
        
        // Execute TerminalOperator
        else
        {
            prg.visualizeTerminal(p.second);
        }
    }
}

void LOOK::display(std::ostream &out)
{
    out << "LOOK";
}

void LOOK::randomize(std::vector<std::pair<int, int>> &params)
{
    int cSize = env.getControlOperators().size();
    int tSize = env.getTerminalOperators().size();

    auto &random = RandomGenerator::get();

    params.clear();
    for (int i = 0; i < 2; ++i)
    {
        if (random.P(0.5))
            params.push_back(std::make_pair<int, int>(1, random.GetInt(0, cSize)));
        else
            params.push_back(std::make_pair<int, int>(0, random.GetInt(0, tSize)));
    }
}

void LOOK::mutate(std::vector<std::pair<int, int>> &params)
{
    randomize(params);
}
