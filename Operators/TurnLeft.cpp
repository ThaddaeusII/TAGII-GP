#include "TurnLeft.h"

#include <iostream>

void TurnLeft::execute(std::shared_ptr<Environment> &env, int &steps)
{
    env->agentDir += 1;
    env->agentDir %= 4;
}

void TurnLeft::display()
{
    std::cout << "turn_left";
}
