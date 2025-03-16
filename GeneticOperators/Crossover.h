#pragma once

#include "Program.h"

class Crossover
{
private:
    double crossoverRate;

protected:
    static void copyInstruction(std::unique_ptr<Program>& program, const std::unique_ptr<Program::Instruction>& instr)
        { program->instructions.push_back(std::make_unique<Program::Instruction>(*instr)); }
    static std::vector<std::unique_ptr<Program::Instruction>>& getInstructions(std::unique_ptr<Program>& program)
        { return program->instructions; }
    static std::shared_ptr<Environment>& getEnv(std::unique_ptr<Program>& program)
        { return program->env; }

public:
    Crossover(double crossoverRate) : crossoverRate(crossoverRate) {}
    double GetCrossoverRate() { return crossoverRate; }
    virtual std::unique_ptr<Program> cross(std::unique_ptr<Program>& program1, std::unique_ptr<Program>& program2) = 0;
};