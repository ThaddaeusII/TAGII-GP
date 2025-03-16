#include <iostream>

#include "GPSystem.h"

int main(int argc, char*argv[])
{
    GPSystem gp;
    std::string path = "Environments/test.env";

    gp.run(
        5,      // Population size
        1,      // Generations
        0.1,    // Mutation rate
        5,      // Max number of initial instructions
        50,     // Number of steps to execute
        path //Path to environment
    );
    return 0;
}