#include "DefaultCrossover.h"

std::unique_ptr<Program> DefaultCrossover::Cross(std::unique_ptr<Program>& program1, std::unique_ptr<Program>& program2)
{
    return std::make_unique<Program>();
}