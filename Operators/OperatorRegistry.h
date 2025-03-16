#pragma once

#include <vector>
#include <memory>

#include "ControlOperator.h"
#include "TerminalOperator.h"

class OperatorRegistry
{
public:
    // -------------- Control Operators --------------

    static std::vector<std::shared_ptr<ControlOperator>>& getControlOperators()
    {
        static std::vector<std::shared_ptr<ControlOperator>> controlOoperators;
        return controlOoperators;
    }

    static void registerControlOperator(std::shared_ptr<ControlOperator> op)
    {
        getControlOperators().push_back(std::move(op));
    }

    static std::shared_ptr<ControlOperator> getControlOperator(int pos)
    {
        return getControlOperators()[pos];
    }

    static std::shared_ptr<ControlOperator> getRandomControlOperator();

    // -------------- Terminal Operators --------------

    static std::vector<std::shared_ptr<TerminalOperator>>& getTerminalOperators()
    {
        static std::vector<std::shared_ptr<TerminalOperator>> terminalOperators;
        return terminalOperators;
    }

    static void registerTerminalOperator(std::shared_ptr<TerminalOperator> op)
    {
        getTerminalOperators().push_back(std::move(op));
    }

    static std::shared_ptr<TerminalOperator> getTerminalOperator(int pos)
    {
        return getTerminalOperators()[pos];
    }

    static std::shared_ptr<TerminalOperator> getRandomTerminalOperator();
};
