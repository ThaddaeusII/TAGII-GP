#include "Environment.h"

#include "RandomGenerator.h"

std::vector<std::shared_ptr<ControlOperator>> &Environment::getControlOperators()
{
    return controlOperators;
}

void Environment::registerControlOperator(std::shared_ptr<ControlOperator> op)
{
    getControlOperators().push_back(std::move(op));
}

std::shared_ptr<ControlOperator> Environment::getControlOperator(int pos)
{
    return getControlOperators()[pos];
}

std::shared_ptr<ControlOperator> Environment::getRandomControlOperator()
{
    auto &random = RandomGenerator::get();
    int idx = random.GetInt(0, getControlOperators().size());
    return getControlOperators()[idx];
}

std::vector<std::shared_ptr<TerminalOperator>> &Environment::getTerminalOperators()
{
    return terminalOperators;
}

void Environment::registerTerminalOperator(std::shared_ptr<TerminalOperator> op)
{
    getTerminalOperators().push_back(std::move(op));
}

std::shared_ptr<TerminalOperator> Environment::getTerminalOperator(int pos)
{
    return getTerminalOperators()[pos];
}

std::shared_ptr<TerminalOperator> Environment::getRandomTerminalOperator()
{
    auto &random = RandomGenerator::get();
    int idx = random.GetInt(0, getTerminalOperators().size());
    return getTerminalOperators()[idx];
}
