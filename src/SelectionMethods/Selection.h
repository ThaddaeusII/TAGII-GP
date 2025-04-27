#pragma once

#include <vector>
#include <string>
#include "Program.h"
#include "Mutation.h"
#include "Crossover.h"

class Selection
{
private:
    std::string name;
    
protected:
    static void copyInstruction(std::unique_ptr<Program>& program, const std::unique_ptr<Program::Instruction>& instr)
        { program->instructions.push_back(std::make_unique<Program::Instruction>(*instr)); }
        
    static std::vector<std::unique_ptr<Program::Instruction>>& getInstructions(std::unique_ptr<Program>& program)
        { return program->instructions; }

    static std::shared_ptr<Environment>& getEnv(std::unique_ptr<Program>& program)
        { return program->env; }

public:
    Selection(std::string name) : name(name) {}
    std::string getName() { return name; }
    virtual void select(std::vector<std::unique_ptr<Program>> &population,
        std::vector<std::unique_ptr<Program>> &children,
        std::shared_ptr<Mutation> &mutator,
        std::shared_ptr<Crossover> &crossover
    ) = 0;
};