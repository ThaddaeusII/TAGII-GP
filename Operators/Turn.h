#pragma once

#include "TerminalOperator.h"

#include <functional>

class Turn : public TerminalOperator
{
private:
    std::function<void()> turnFunction;
    bool left;

public:
    Turn(Environment& env, std::function<void()> turnFunction, bool left) : TerminalOperator(env), turnFunction(turnFunction), left(left) {}
    void execute() override;
    void display() override;
};