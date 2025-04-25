#pragma once

#include <vector>
#include <memory>
#include <iostream>

class Program;
class Environment;

class ControlOperator
{
private:

protected:
    Environment& env;

public:
    ControlOperator(Environment& env) : env(env) {}
    virtual void execute(Program& prg, int pos, std::vector<std::pair<int, int>>& params) = 0;
    virtual void visualize(Program& prg, int pos, std::vector<std::pair<int, int>>& params) = 0;
    virtual void display(std::ostream &out = std::cout) = 0;
    virtual void randomize(std::vector<std::pair<int, int>>& params) = 0;
    virtual void mutate(std::vector<std::pair<int, int>>& params) = 0;
};