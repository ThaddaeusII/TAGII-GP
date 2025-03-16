#include <iostream>

#include "GPSystem.h"

int main(int argc, char*argv[])
{
    GPSystem gp;
    std::string path = "Environments/santafe.env";

    gp.run(
        100,     // Population size
        200,     // Generations
        0.75,     // Crossover rate
        0.25,     // Mutation rate
        5,       // Max number of initial instructions
        400,      // Number of steps to execute
        path     //Path to environment
    );
    return 0;
}