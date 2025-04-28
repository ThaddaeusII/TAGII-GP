#include "Program.h"

#include <iomanip>

#include "RandomGenerator.h"

int Program::findReference(int pos, int ref)
{
    for (size_t i = pos + 1; i < instructions.size(); ++i)
        if (instructions[i]->reference == ref)
            return i;
    return -1;
}

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
        instructions.push_back(std::make_unique<Instruction>(env, num));
    }
}

void Program::execute()
{
    // Resets environment and executionQueue
    reset();

    while (!complete())
    {
        // Start program if queue is empty (allows repeat runs if max steps not used up)
        if (!running())
            start();

        step();
    }
    evaluateFitness(); // Update program fitness
}

void Program::start()
{
    // Schedule start: function, type (1 = control, 0 = terminal), ref # (line # or terminal #)
    executionQueue.push_front(std::make_tuple([this](){ stepControl(0); }, 1, 0));
}

void Program::step()
{
    // If program is done, exit
    if (complete())
        return;

    // Get instruction out of queue, then run
    auto current = std::get<0>(executionQueue.front());
    executionQueue.pop_front();
    current();
}

void Program::stepControl(int pos)
{
    // Execute the control operator
    auto &instr = instructions[pos];
    instr->op->execute(*this, pos, instr->params);
}

void Program::stepTerminal(int op)
{
    env->getTerminalOperator(op)->execute();
}

bool Program::complete()
{
    return env->getCurSteps() <= 0 || instructions.empty();
}

bool Program::running()
{
    return !executionQueue.empty();
}

void Program::reset()
{
    env->reset();
    executionQueue.clear();
}

void Program::wait()
{
    env->setCurSteps(env->getCurSteps() - 1);
}

void Program::evaluateFitness()
{
    fitness = env->getFitness();
}

void Program::scheduleInstructionFront(int pos, std::pair<int, int> &param)
{
    if (param.first == 0) // Terminal
    {
        executionQueue.push_front(std::make_tuple([this, param](){ stepTerminal(param.second); }, param.first, param.second));
        return;
    }
    int refPos = findReference(pos, param.second);
    if (refPos == -1) // No refernece, wait
    {
        executionQueue.push_front(std::make_tuple([this](){ wait(); }, -1, -1));
        return;
    }
    executionQueue.push_front(std::make_tuple([this, refPos](){ stepControl(refPos); }, param.first, refPos));
}

void Program::scheduleInstructionBack(int pos, std::pair<int, int> &param)
{
    if (param.first == 0) // Terminal
    {
        executionQueue.push_back(std::make_tuple([this, &param](){ stepTerminal(param.second); }, param.first, param.second));
        return;
    }
    int refPos = findReference(pos, param.second);
    if (refPos == -1) // No refernece, wait
    {
        executionQueue.push_back(std::make_tuple([this](){ wait(); }, -1, -1));
        return;
    }
    executionQueue.push_front(std::make_tuple([this, &refPos](){ stepControl(refPos); }, param.first, refPos));
}

void Program::display(std::ostream &out)
{
    int line = 1;
    for (auto &i : instructions)
    {
        out << "[" << line << "]: [" << i->reference << ", ";
        i->op->display(out);
        for (auto &p : i->params)
        {
            if (p.first)
                out << ", " << "(I, " << p.second << ")";
            else
            {
                out << ", (T, ";
                env->getTerminalOperator(p.second)->display(out);
                out << ")";
            }
        }
        out << "]" << std::endl;
        line++;
    }
}

void Program::displayNextInstruction(std::ostream &out)
{
    if (executionQueue.empty())
    {
        out << "Instruction: [RESTART]" << std::endl;
        return;
    }

    int type = std::get<1>(executionQueue.front());
    int idx = std::get<2>(executionQueue.front());

    if (type == -1) // Wait
    {
        out << "Instruction: [WAIT]" << std::endl;
        return;
    }

    if (type == 0) // Terminal
    {
        out << "Instruction: [";
        env->getTerminalOperator(idx)->display(out);
        out << "]" << std::endl;
        return;
    }
    
    // Control
    out << "Instruction: [";
    instructions[idx]->op->display(out);
    out << "]" << std::endl;
}

int Program::getFitness()
{
    return fitness;
}

int Program::getSize()
{
    return instructions.size();
}

std::vector<std::string> Program::getInstructions()
{
    // Get instructions as a string
    std::ostringstream oss;
    display(oss);
    
    // Split into lines
    std::vector<std::string> lines;
    std::istringstream stream(oss.str());
    std::string line;
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    return lines;
}

Program::Instruction::Instruction(std::shared_ptr<Environment> env, int count)
{
    auto &random = RandomGenerator::get();
    reference = random.GetInt(0, count + 1);
    op = env->getRandomControlOperator();
    op->randomize(params);
}
