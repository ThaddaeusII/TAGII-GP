#pragma once

#include <string>
#include "Program.h"

class Mutation
{
private:
    double mutationRate;
    std::string name;

protected:
    static std::vector<std::unique_ptr<Program::Instruction>>& getInstructions(std::unique_ptr<Program>& program)
        { return program->instructions; }

    static std::shared_ptr<Environment>& getEnv(std::unique_ptr<Program>& program)
        { return program->env; }

    static void addInstruction(std::unique_ptr<Program>& program, int pos)
        { program->instructions.insert(program->instructions.begin() + pos, std::make_unique<Program::Instruction>(program->env, program->instructions.size() + 1)); }

    static void deleteInstruction(std::unique_ptr<Program>& program, int pos)
        { program->instructions.erase(program->instructions.begin() + pos); }

public:
    Mutation(double mutationRate, std::string name) : mutationRate(mutationRate), name(name) {}
    std::string getName() { return name; }
    double GetMutationRate() { return mutationRate; }
    virtual void mutate(std::unique_ptr<Program> &program) = 0;
};