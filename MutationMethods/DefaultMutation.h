#pragma once

#include "Mutation.h"

class DefaultMutation : public Mutation
{
private:

public:
    DefaultMutation(double mutationRate, std::string name) : Mutation(mutationRate, name) {}
    virtual void mutate(std::unique_ptr<Program> &program);
};