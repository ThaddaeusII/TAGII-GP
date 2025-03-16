#include "Move.h"

#include <iostream>

void Move::execute(std::shared_ptr<Environment> &env, int &steps)
{
    env->move();
}

void Move::display()
{
    std::cout << "move";
}
