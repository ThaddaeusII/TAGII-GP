#pragma once

#include "Instruction.h"
#include "Environment.h"

class LookForward : public Instruction {
public:
    void execute(Environment& env) override;
    void display() override;
};