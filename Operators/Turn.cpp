#include "Turn.h"

#include <iostream>

#include "Environment.h"

void Turn::execute(int &steps)
{
    turnFunction();
}

void Turn::display()
{
    if (left)
        std::cout << "turn_left";
    else
        std::cout << "turn_right";
}
