#include <iostream>

#include "GPSystem.h"

int main(int argc, char*argv[])
{
    GPSystem gp;
    gp.run(3,   // Population size
        100,    // Generations
        0.1);   // Mutation rate
    gp.display();

    return 0;
}