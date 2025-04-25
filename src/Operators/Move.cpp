#include "Move.h"

#include <iostream>

#include "Environment.h"

void Move::execute()
{
    moveFunction();
}

void Move::display(std::ostream &out)
{
    out << "move";
}
