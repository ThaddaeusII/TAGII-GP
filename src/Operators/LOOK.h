#pragma once

#include "ControlOperator.h"

#include <functional>

class LOOK : public ControlOperator
{
private:
    std::function<bool()> lookFunction;

public:
    LOOK(Environment& env, std::function<bool()> lookFunction) : ControlOperator(env), lookFunction(lookFunction) {}
    void execute(Program &prg, int pos, std::vector<std::pair<int, int>> &params) override;
    void display(std::ostream &out = std::cout) override;
    void randomize(std::vector<std::pair<int, int>> &params) override;
    void mutate(std::vector<std::pair<int, int>> &params) override;
};