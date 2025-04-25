#pragma once

#include <memory>
#include <iostream>

class Program;
class Environment;

class TerminalOperator
{
private:

protected:
    Environment& env;

public:
    TerminalOperator(Environment& env) : env(env) {}
    virtual void execute() = 0;
    virtual void display(std::ostream &out = std::cout) = 0;
};