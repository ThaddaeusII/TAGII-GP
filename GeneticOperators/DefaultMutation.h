#pragma once

#include "Mutation.h"
#include "Program.h"

class DefaultMutation : public Mutation
{
private:

public:
    virtual ~DefaultMutation() = default;
    void Mutate(std::unique_ptr<Program> &program) override;
};