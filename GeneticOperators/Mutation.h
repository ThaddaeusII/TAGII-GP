#pragma once

#include "Program.h"

class Mutation
{
private:
    double mutationRate;

protected:
    static std::vector<std::unique_ptr<Program::Instruction>>& getInstructions(std::unique_ptr<Program>& program)
        { return program->instructions; }

    static void addInstruction(std::unique_ptr<Program>& program, int pos)
        { program->instructions.insert(program->instructions.begin() + pos, std::make_unique<Program::Instruction>(program->instructions.size() + 1)); }

    static void deleteInstruction(std::unique_ptr<Program>& program, int pos)
        { program->instructions.erase(program->instructions.begin() + pos); }

public:
    Mutation(double mutationRate) : mutationRate(mutationRate) {}
    double GetMutationRate() { return mutationRate; }
    virtual void mutate(std::unique_ptr<Program> &program) = 0;
};