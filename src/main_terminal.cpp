#include <iostream>

#include "GPSystem.h"

// Selection methods
#include "TournamentSelection.h"

// Mutation methods
#include "DefaultMutation.h"

// Crossover methods
#include "DefaultCrossover.h"

// Environments
#include "SantaFeEnvironment.h"
#include "PacmanEnvironment.h"

void selectSelectionMethod(GPSystem *gp)
{
    std::string defaultSelection = "Tournament Selection (size 7)";

    std::cout << std::endl << "==== Selection Method ====" << std::endl;
    std::cout << "1. " << defaultSelection << std::endl;
    std::cout << "Select option: ";

    int choice;
    std::cin >> choice;
    switch(choice)
    {
        case 1:
            gp->setSelectionMethod(std::make_shared<TournamentSelection>(defaultSelection));
            break;
        default:
            std::cout << "Invalid option" << std::endl;
    }
}

void selectMutationMethod(GPSystem *gp)
{
    std::string defaultMutation = "Random Uniform Mutation";

    std::cout << std::endl << "==== Mutation Method ====" << std::endl;
    std::cout << "1. " << defaultMutation << std::endl;
    std::cout << "Select option: ";

    int choice;
    std::cin >> choice;
    switch(choice)
    {
        case 1:
            gp->setMutationMethod(std::make_shared<DefaultMutation>(gp->getMutationRate(), defaultMutation));
            break;
        default:
            std::cout << "Invalid option" << std::endl;
    }
}

void selectCrossoverMethod(GPSystem *gp)
{
    std::string defaultCrossover = "One-Point Crossover (max copy of 10)";

    std::cout << std::endl << "==== Mutation Method ====" << std::endl;
    std::cout << "1. " << defaultCrossover << std::endl;
    std::cout << "Select option: ";

    int choice;
    std::cin >> choice;
    switch(choice)
    {
        case 1:
            gp->setCrossoverMethod(std::make_shared<DefaultCrossover>(gp->getCrossoverRate(), defaultCrossover));
            break;
        default:
            std::cout << "Invalid option" << std::endl;
    }
}

void selectEnvironment(GPSystem *gp)
{
    std::string antTrailEnvironment = "Santa Fe Ant Trail";
    std::string mazeEnvironment = "Maze";
    std::string pacmanEnvironment = "Pacman";

    std::cout << std::endl << "==== Mutation Method ====" << std::endl;
    std::cout << "1. " << antTrailEnvironment << std::endl;
    std::cout << "2. " << mazeEnvironment << std::endl;
    std::cout << "3. " << pacmanEnvironment << std::endl;
    std::cout << "Select option: ";

    int choice;
    std::cin >> choice;
    switch(choice)
    {
        case 1:
        {
            auto env = std::make_shared<SantaFeEnvironment>(antTrailEnvironment);
            env->load("./Environments/santafe.env");
            gp->SetEnvironment(env);
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            auto env = std::make_shared<PacmanEnvironment>(pacmanEnvironment);
            env->load("./Environments/pacman.env");
            gp->SetEnvironment(env);
            break;
        }
        default:
            std::cout << "Invalid option" << std::endl;
    }
}

void displayMenu() {
    std::cout << std::endl << "==== Genetic Programming System ====" << std::endl;
    std::cout << "1. Modify parameters" << std::endl;
    std::cout << "2. Run evolution" << std::endl;
    std::cout << "3. Display environment" << std::endl;
    std::cout << "4. Visualize program" << std::endl;
    std::cout << "5. Display program" << std::endl;
    std::cout << "6. Display stats" << std::endl;
    std::cout << "7. Reset population" << std::endl;
    std::cout << "8. Save population" << std::endl;
    std::cout << "9. Load population" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Select option: ";
}

void selectParameters(GPSystem *gp)
{
    bool running = true;
    while (running)
    {
        gp->displayParameters();
        std::cout << "0. Exit" << std::endl;
        std::cout << "Select option: ";
        int choice;
        std::cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int size;
                std::cout << "New size: ";
                std::cin >> size;
                if (size < 1)
                    std::cout << "Invalid size (size >= 1)" << std::endl;
                else
                    gp->setPopulationSize(size);
                break;
            }

            case 2:
            {
                int gens;
                std::cout << "New generations: ";
                std::cin >> gens;
                if (gens < 1)
                    std::cout << "Invalid generations (gens >= 1)" << std::endl;
                else
                    gp->setGenerations(gens);
                break;
            }

            case 3:
            {
                double rate;
                std::cout << "New mutation rate: ";
                std::cin >> rate;
                if (rate > 1.0 || rate < 0.0)
                    std::cout << "Invalid rate (0.0 <= rate <= 1.0)" << std::endl;
                else
                    gp->setMutationRate(rate);
                break;
            }

            case 4:
            {
                double rate;
                std::cout << "New crossover rate: ";
                std::cin >> rate;
                if (rate > 1.0 || rate < 0.0)
                    std::cout << "Invalid rate (0.0 <= rate <= 1.0)" << std::endl;
                else
                    gp->setCrossoverRate(rate);
                break;
            }

            case 5:
            {
                int size;
                std::cout << "New max initial instructions: ";
                std::cin >> size;
                if (size < 0)
                    std::cout << "Invalid size (size >= 0)" << std::endl;
                else
                    gp->setMaxInstructions(size);
                break;
            }

            case 6:
            {
                int steps;
                std::cout << "New max steps a program can run: ";
                std::cin >> steps;
                if (steps < 1)
                    std::cout << "Invalid steps (steps >= 1)" << std::endl;
                else
                    gp->setMaxSteps(steps);
                break;
            }

            case 7:
                selectSelectionMethod(gp);
                break;

            case 8:
                selectMutationMethod(gp);
                break;

            case 9:
                selectCrossoverMethod(gp);
                break;

            case 10:
                selectEnvironment(gp);
                break;

            case 0:
                running = false;
                break;

            default:
                std::cout << "Invalid option.\n";
        }
    }
}

int main(int argc, char*argv[])
{
    GPSystem gp;
    bool running = true;

    while (running)
    {
        displayMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
            case 1:
                selectParameters(&gp);
                break;

            case 2:
                gp.evolve();
                break;

            case 3:
                std::cout << std::endl;
                gp.displayEnvironment();
                std::cout << std::endl;
                std::cout << "Press [ENTER] to continue...";
                std::cin.get();
                break;

            case 4:
            {
                int idx;
                std::cout << "Visualize which program (index)? ";
                std::cin >> idx;
                break;
            }

            case 5:
            {
                int idx;
                std::cout << "Display which program (index)? Select -1 for all. ";
                std::cin >> idx;
                if (idx == -1)
                    gp.displayAllPrograms();
                else
                    gp.displayProgram(idx);
                break;
            }

            case 6:
                std::cout << std::endl;
                gp.displayStats();
                std::cout << std::endl;
                std::cout << "Press [ENTER] to continue...";
                std::cin.get();
                break;

            case 7:
                gp.reset();
                break;

            case 8:
                break;

            case 9:
                break;

            case 0:
                running = false;
                break;

            default:
                std::cout << "Invalid option.\n";
        }
    }

    return 0;
}