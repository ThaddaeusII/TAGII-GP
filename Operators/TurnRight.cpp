#include "TurnRight.h"

#include <iostream>

void TurnRight::execute(std::shared_ptr<Environment> &env, int &steps)
{
    env->agentDir -= 1;
    env->agentDir %= 4;
}

void TurnRight::display()
{
    std::cout << "turn_right";
}
