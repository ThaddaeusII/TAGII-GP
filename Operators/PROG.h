#pragma once

#include "ControlOperator.h"

class PROG : public ControlOperator
{
private:
    int x;

public:
    PROG(int x = 2) : x(x) {}
    void execute(Program &prg, std::shared_ptr<Environment> &env, int pos, std::vector<std::pair<int, int>> &params) override;
    void display() override;
    void randomize(std::vector<std::pair<int, int>> &params) override;
};