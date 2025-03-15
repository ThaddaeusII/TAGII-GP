#pragma once

#include "Instruction.h"
#include "Environment.h"

class TurnRight : public Instruction {
public:
    void execute(Environment& env) override;
    void display() override;
};