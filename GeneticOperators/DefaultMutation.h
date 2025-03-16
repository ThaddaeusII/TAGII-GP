#pragma once

#include "Mutation.h"
#include "Program.h"

class DefaultMutation : public Mutation
{
private:

public:
    DefaultMutation(double mutationRate) : Mutation(mutationRate) {}
    void mutate(std::unique_ptr<Program> &program) override;
};