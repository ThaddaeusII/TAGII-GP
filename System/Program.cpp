#include "Program.h"

#include "RandomGenerator.h"

void Program::getInput()
{
    if (waitForInput)
    {
        std::cout << "\nPress [ENTER] to begin, [x] to skip to the end..." << std::endl;
        char x = std::cin.get();
        if (x == 'x' || x == 'X')
            waitForInput = false;
    }
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
    env->reset();
    while (env->getCurSteps() > 0)
    {
        executeControl(0);
    }
    evaluateFitness();
}

void Program::executeControl(int pos, int ref)
{
    if (instructions.empty())
        env->setCurSteps(0);
    if (env->getCurSteps() <= 0)
        return;

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
            env->setCurSteps(env->getCurSteps() - 1);
            return;
        }
    }

    // Execute the instruction
    auto &instr = instructions[pos];
    instr->op->execute(*this, pos, instr->params);
}

void Program::executeTerminal(int op)
{
    if (env->getCurSteps() <=0)
        return;
    env->getTerminalOperator(op)->execute();
}

void Program::visualize()
{
    waitForInput = true;
    std::cout << "\033[2J\033[H";
    std::cout << "Starting program visualization...\n\n";

    if (!env)
    {
        std::cerr << "No environment attached to program.\n\n";
        return;
    }

    std::cout << "Program:\n";
    display();
    getInput();

    env->reset();

    while (env->getCurSteps() > 0)
    {
        visualizeControl(0);
    }

    evaluateFitness();

    std::cout << "\033[2J\033[H";
    std::cout << "Program finished.\n";
    std::cout << "Steps remaining: " << env->getCurSteps() << " / " << env->getMaxSteps() << "\n";
    std::cout << "Final environment:\n";
    env->display();
    std::cout << "\nFinal fitness: " << env->getFitness() << "\n";
}

void Program::visualizeControl(int pos, int ref)
{
    if (env->getCurSteps() <= 0 || instructions.empty())
        return;

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
        if (!found)
        {
            std::cout << "\033[2J\033[H";
            std::cout << "Steps remaining: " << env->getCurSteps() << " / " << env->getMaxSteps() << "\n";
            std::cout << "Executing terminal [WAIT - unresolved reference]\n\n";
            env->display();
            std::cout << "\nProgram:\n";
            display();
            getInput();
            env->setCurSteps(env->getCurSteps() - 1);
            return;
        }
    }

    auto &instr = instructions[pos];

    std::cout << "\033[2J\033[H";
    std::cout << "Steps remaining: " << env->getCurSteps() << " / " << env->getMaxSteps() << "\n";
    std::cout << "Executing control #" << pos << ": ";
    instr->op->display();
    std::cout << " with params:";
    for (auto &p : instr->params)
    {
        if (p.first)
            std::cout << " I[" << p.second << "]";
        else
        {
            std::cout << " T[";
            env->getTerminalOperator(p.second)->display();
            std::cout << "]";
        }
    }

    std::cout << "\n\n";
    env->display();
    std::cout << "\nProgram:\n";
    display();
    getInput();

    instr->op->visualize(*this, pos, instr->params);
}

void Program::visualizeTerminal(int op)
{
    if (env->getCurSteps() <= 0) return;

    std::cout << "\033[2J\033[H";
    std::cout << "Steps remaining: " << env->getCurSteps() << " / " << env->getMaxSteps() << "\n";
    std::cout << "Executing terminal: ";
    env->getTerminalOperator(op)->display();
    std::cout << "\n\n";
    env->display();
    std::cout << "\nProgram:\n";
    display();
    getInput();

    env->getTerminalOperator(op)->execute();
}

void Program::evaluateFitness()
{
    fitness = env->getFitness();
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
