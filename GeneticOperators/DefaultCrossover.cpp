#include "DefaultCrossover.h"

std::unique_ptr<Program> DefaultCrossover::Cross(std::unique_ptr<Program>& program1, std::unique_ptr<Program>& program2, std::shared_ptr<Environment> &environment)
{
    return std::make_unique<Program>(environment);
}