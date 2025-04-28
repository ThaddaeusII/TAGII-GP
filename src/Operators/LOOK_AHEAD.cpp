#include "LOOK_AHEAD.h"

#include <iostream>

#include "Program.h"
#include "Environment.h"
#include "RandomGenerator.h"

void LOOK_AHEAD::execute(Program &prg, int pos, std::vector<std::pair<int, int>> &params)
{
    auto p = params[!lookFunction()];
    prg.scheduleInstructionFront(pos, p);
}

void LOOK_AHEAD::display(std::ostream &out)
{
    out << name;
}

void LOOK_AHEAD::randomize(std::vector<std::pair<int, int>> &params)
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

void LOOK_AHEAD::mutate(std::vector<std::pair<int, int>> &params)
{
    randomize(params);
}
