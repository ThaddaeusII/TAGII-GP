#include "Program.h"

#include <iostream>

#include "OperatorRegistry.h"
#include "RandomGenerator.h"

Program::Program(std::shared_ptr<Environment> env)
{
    this->env = env;
}

void Program::initialize(int numInstructions)
{
    fitness = -1;
    int num = RandomGenerator::get().GetInt(0, numInstructions + 1);
    for (int i = 0; i < num; ++i)
    {
        instructions.push_back(std::make_unique<Instruction>(num));
    }
}

void Program::maxSteps(int steps)
{
    this->steps = steps;
}

void Program::executeControl(int pos, int ref)
{
    if (steps <= 0 || instructions.empty())
    {
        steps = 0;
        return;
    }

    // If reference is specified, start looking for the referenced instruction after the current one
    if (ref != -1)
    {
        bool found = false;
        for (size_t i = pos + 1; i < instructions.size(); ++i)
        {
            if (instructions[i]->reference == ref)
            {
                pos = i;
                found = true;
                break;
            }
        }

        // If the referenced instruction doesn't exist, do nothing
        if (!found)
        {
            steps--;
            return;
        }
    }

    // Execute the instruction
    auto &instr = instructions[pos];
    instr->op->execute(*this, env, pos, instr->params);
}

void Program::executeTerminal(int op)
{
    if (steps <=0)
        return;
    OperatorRegistry::getTerminalOperator(op)->execute(env, steps);
    steps--;
}

void Program::display()
{
    int line = 1;
    for (auto &i : instructions)
    {
        std::cout << "[" << line << "]: [" << i->reference << ", ";
        i->op->display();
        for (auto &p : i->params)
        {
            if (p.first)
                std::cout << ", " << "(I, " << p.second << ")";
            else
            {
                std::cout << ", (T, ";
                OperatorRegistry::getTerminalOperator(p.second)->display();
                std::cout << ")";
            }
        }
        std::cout << "]" << std::endl;
        line++;
    }
}

int Program::getFitness()
{
    return fitness;
}

int Program::getSteps()
{
    return steps;
}

int Program::getSize()
{
    return instructions.size();
}

void Program::evaluateFitness()
{
    fitness = env->food;
}

Program::Instruction::Instruction(int count)
{
    auto &random = RandomGenerator::get();
    reference = random.GetInt(0, count + 1);
    op = OperatorRegistry::getRandomControlOperator();
    op->randomize(params);
}
