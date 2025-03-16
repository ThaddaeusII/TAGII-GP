#include "OperatorRegistry.h"
#include "RandomGenerator.h"

/* 
 * ------------------------------------------------------------------------------
 *                      !!! ADD ALL OPERATORS HERE !!!
 * ------------------------------------------------------------------------------
 */

// Control Operators
#include "PROG.h"
#include "LOOK.h"

// Terminal Operators
#include "Move.h"
#include "TurnLeft.h"
#include "TurnRight.h"

void registerAllOperators()
{
    // Control Operators
    OperatorRegistry::registerControlOperator(std::make_shared<PROG>(2));
    OperatorRegistry::registerControlOperator(std::make_shared<PROG>(3));
    OperatorRegistry::registerControlOperator(std::make_shared<LOOK>());

    // Terminal Operators
    OperatorRegistry::registerTerminalOperator(std::make_shared<Move>());
    OperatorRegistry::registerTerminalOperator(std::make_shared<TurnLeft>());
    OperatorRegistry::registerTerminalOperator(std::make_shared<TurnRight>());
}

// Change how random operators are selected, uniform by default

std::shared_ptr<ControlOperator> OperatorRegistry::getRandomControlOperator()
{
    auto &random = RandomGenerator::get();
    int idx = random.GetInt(0, getControlOperators().size());
    return getControlOperators()[idx];
}

std::shared_ptr<TerminalOperator> OperatorRegistry::getRandomTerminalOperator()
{
    auto &random = RandomGenerator::get();
    int idx = random.GetInt(0, getTerminalOperators().size());
    return getTerminalOperators()[idx];
}

struct OperatorAutoRegister
{
    OperatorAutoRegister() { registerAllOperators(); }
};
static OperatorAutoRegister autoRegister;