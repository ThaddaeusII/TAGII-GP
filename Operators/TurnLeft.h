#pragma once

#include "TerminalOperator.h"

class TurnLeft : public TerminalOperator
{
private:

public:
    void execute(std::shared_ptr<Environment> &env, int &steps) override;
    void display() override;
};