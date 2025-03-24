#include "Program.h"

#include "RandomGenerator.h"

Program::Program(std::shared_ptr<Environment> env)
{
    this->env = env;
}

void Program::initPerfect()
{
    std::vector<std::pair<int, int>> params;
    instructions.clear();

    instructions.push_back(std::make_unique<Instruction>(env, 0));
    instructions[0]->reference = 0;
    instructions[0]->op = env->getControlOperator(2);
    params.clear();
    params.push_back(std::make_pair<int, int>(0, 0));
    params.push_back(std::make_pair<int, int>(1, 1));
    instructions[0]->params = params;

    instructions.push_back(std::make_unique<Instruction>(env, 0));
    instructions[1]->reference = 1;
    instructions[1]->op = env->getControlOperator(0);
    params.clear();
    params.push_back(std::make_pair<int, int>(1, 2));
    params.push_back(std::make_pair<int, int>(0, 0));
    instructions[1]->params = params;

    instructions.push_back(std::make_unique<Instruction>(env, 0));
    instructions[2]->reference = 2;
    instructions[2]->op = env->getControlOperator(0);
    params.clear();
    params.push_back(std::make_pair<int, int>(1, 3));
    params.push_back(std::make_pair<int, int>(1, 3));
    instructions[2]->params = params;

    instructions.push_back(std::make_unique<Instruction>(env, 0));
    instructions[3]->reference = 3;
    instructions[3]->op = env->getControlOperator(2);
    params.clear();
    params.push_back(std::make_pair<int, int>(1, 2));
    params.push_back(std::make_pair<int, int>(0, 1));
    instructions[3]->params = params;
}

void Program::initialize(int numInstructions)
{
    fitness = -1;
    int num = RandomGenerator::get().GetInt(0, numInstructions + 1);
    for (int i = 0; i < num; ++i)
    {
        instructions.push_back(std::make_unique<Instruction>(env, num));
    }
}

void Program::executeControl(int pos, int ref)
{
    if (curSteps <= 0 || instructions.empty())
    {
        curSteps = 0;
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
            curSteps--;
            return;
        }
    }

    // Execute the instruction
    auto &instr = instructions[pos];
    instr->op->execute(*this, pos, instr->params);
}

void Program::executeTerminal(int op)
{
    if (curSteps <=0)
        return;
    env->getTerminalOperator(op)->execute(curSteps);
    curSteps--;
}

void Program::evaluateFitness()
{
    fitness = env->getFitness();
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
                env->getTerminalOperator(p.second)->display();
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
    return curSteps;
}

void Program::setSteps(int steps)
{
    curSteps = steps;
}

int Program::getSize()
{
    return instructions.size();
}

Program::Instruction::Instruction(std::shared_ptr<Environment> env, int count)
{
    auto &random = RandomGenerator::get();
    reference = random.GetInt(0, count + 1);
    op = env->getRandomControlOperator();
    op->randomize(params);
}
