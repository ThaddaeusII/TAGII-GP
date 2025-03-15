#pragma once

#include "Instruction.h"
#include "Environment.h"

class TurnLeft : public Instruction {
public:
    void execute(Environment& env) override;
    void display() override;
};