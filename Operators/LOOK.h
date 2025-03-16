#pragma once

#include "ControlOperator.h"

class LOOK : public ControlOperator
{
private:

public:
    void execute(Program &prg, std::shared_ptr<Environment> &env, int pos, std::vector<std::pair<int, int>> &params) override;
    void display() override;
    void randomize(std::vector<std::pair<int, int>> &params) override;
};