#include "Move.h"

#include <iostream>

#include "Environment.h"

void Move::execute(int &steps)
{
    moveFunction();
}

void Move::display()
{
    std::cout << "move";
}
