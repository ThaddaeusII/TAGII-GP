#pragma once

#include "ControlOperator.h"

#include <functional>

class LOOK_AHEAD : public ControlOperator
{
private:
    std::function<bool()> lookFunction;
    std::string name;

public:
    LOOK_AHEAD(Environment& env, std::function<bool()> lookFunction, std::string name = "LOOK_AHEAD") : ControlOperator(env), lookFunction(lookFunction), name(name) {}
    void execute(Program &prg, int pos, std::vector<std::pair<int, int>> &params) override;
    void visualize(Program &prg, int pos, std::vector<std::pair<int, int>> &params) override;
    void display() override;
    void randomize(std::vector<std::pair<int, int>> &params) override;
    void mutate(std::vector<std::pair<int, int>> &params) override;
};