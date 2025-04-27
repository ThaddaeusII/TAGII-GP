#include "DefaultCrossover.h"

#include "RandomGenerator.h"

std::unique_ptr<Program> DefaultCrossover::cross(std::unique_ptr<Program> &program1, std::unique_ptr<Program> &program2)
{
    auto &random = RandomGenerator::get();
    if (random.P(GetCrossoverRate()))
    {
        // If crossover, mix subsets of intructions from parents
        auto child = std::make_unique<Program>(getEnv(program1));

        auto &instr1 = getInstructions(program1);
        auto &instr2 = getInstructions(program2);
        int xpoint1 = random.GetInt(0, instr1.size());
        int xpoint2 = random.GetInt(0, instr2.size());
        
        for (int i = 0; i < std::min(xpoint1, maxCopySize); ++i)
            copyInstruction(child, instr1[i]);
            
        for (int i = xpoint2; i < std::min((int)instr2.size(), xpoint2 + maxCopySize); ++i)
            copyInstruction(child, instr2[i]);
        
        return child;
    }
    else
    {
        // No crossover, copy parent
        auto child = std::make_unique<Program>(getEnv(program1));
        auto &instr = (random.P(0.5)) ? getInstructions(program1) : getInstructions(program2);
        for (size_t i = 0; i < instr.size(); ++i)
            copyInstruction(child, instr[i]);
        return child;
    }
}