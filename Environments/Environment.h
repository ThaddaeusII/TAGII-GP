#pragma once

#include <string>
#include <memory>

#include "ControlOperator.h"
#include "TerminalOperator.h"

class Environment
{
private:
    std::string name;
    std::vector<std::shared_ptr<ControlOperator>> controlOperators;
    std::vector<std::shared_ptr<TerminalOperator>> terminalOperators;

protected:
    int fitness = -1;
    int curSteps = -1;
    int maxSteps = -1;

public:
    Environment(std::string name) : name(name) {}

    // -------------- Control Operators --------------
    std::vector<std::shared_ptr<ControlOperator>>& getControlOperators();
    void registerControlOperator(std::shared_ptr<ControlOperator> op);
    std::shared_ptr<ControlOperator> getControlOperator(int pos);
    std::shared_ptr<ControlOperator> getRandomControlOperator();

    // -------------- Terminal Operators --------------
    std::vector<std::shared_ptr<TerminalOperator>>& getTerminalOperators();
    void registerTerminalOperator(std::shared_ptr<TerminalOperator> op);
    std::shared_ptr<TerminalOperator> getTerminalOperator(int pos);
    std::shared_ptr<TerminalOperator> getRandomTerminalOperator();

    // General functions
    std::string getName() { return name; }
    int getCurSteps() { return curSteps; }
    int getMaxSteps() { return maxSteps; }
    int getFitness() { return fitness; }

    void setCurSteps(int steps) { curSteps = steps; }
    void setMaxSteps(int steps) { maxSteps = steps; }

    // Required overrides
    virtual void registerAllOperators() = 0;
    virtual void reset() = 0;
    virtual void load(std::string envPath) = 0;
    virtual void display() = 0;
};