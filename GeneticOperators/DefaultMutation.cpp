#include "DefaultMutation.h"

#include "OperatorRegistry.h"
#include "RandomGenerator.h"

void DefaultMutation::mutate(std::unique_ptr<Program> &program)
{
    auto &random = RandomGenerator::get();
    auto &instr = getInstructions(program);
    int s = instr.size();

    // Each intruction has a % chance to mutate
    for (int i = s - 1; i >= 0; --i)
    {
        if (random.P(GetMutationRate()))
        {
            // Mutation occured, what type?
            double choice = random.GetDouble(0.0, 1.0);
            if (choice < 0.5)
            {
                // 50% chance to modify this instruction
                if (random.P(0.5)) // 50% chance to modify params
                    instr[i]->op->mutate(instr[i]->params);
                else // 50% chance to swap operator (and randomize params)
                {
                    instr[i]->op = OperatorRegistry::getRandomControlOperator();
                    instr[i]->op->randomize(instr[i]->params);
                }
            }
            else if (choice < 0.75)
            {
                // 25% chance to delete this instruction
                deleteInstruction(program, i);
            }
            else
            {
                // 25% chance to add an instruction here
                addInstruction(program, i);
            }
        }
    }
}