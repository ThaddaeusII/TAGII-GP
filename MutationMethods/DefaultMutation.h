#pragma once

#include "Mutation.h"

class DefaultMutation : public Mutation
{
private:

public:
    DefaultMutation(double mutationRate) : Mutation(mutationRate) {}
    virtual void mutate(std::unique_ptr<Program> &program);
};