#pragma once

#include "TerminalOperator.h"

#include <functional>

class Move : public TerminalOperator
{
private:
    std::function<void()> moveFunction;

public:
    Move(Environment& env, std::function<void()> moveFunction) : TerminalOperator(env), moveFunction(moveFunction) {}
    void execute() override;
    void display() override;
};