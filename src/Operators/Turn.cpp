#include "Turn.h"

#include <iostream>

#include "Environment.h"

void Turn::execute()
{
    turnFunction();
}

void Turn::display(std::ostream &out)
{
    if (left)
        out << "turn_left";
    else
        out << "turn_right";
}
