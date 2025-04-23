#pragma once

#include "ControlOperator.h"

class PROG : public ControlOperator
{
private:
    int x;

public:
    PROG(Environment& env, int x = 2) : ControlOperator(env), x(x) {}
    void execute(Program &prg, int pos, std::vector<std::pair<int, int>> &params) override;
    void visualize(Program& prg, int pos, std::vector<std::pair<int, int>>& params) override;
    void display() override;
    void randomize(std::vector<std::pair<int, int>> &params) override;
    void mutate(std::vector<std::pair<int, int>> &params) override;
};