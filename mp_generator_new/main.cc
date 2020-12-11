#include "header/coord.h"
#include "header/functions.h"

int main()
{
    bool status = true;
    int prog_func;
    char stats;
    while (status)
    {
        std::cout<< "===============================================================================" << std::endl;
        std::cout<< "+       Prismatic Mesh and Particle Generating Program (for CB-Geo MPM)       +" << std::endl;
        std::cout<< "+                         *created by: Arif Yunando S                         +" << std::endl;
        std::cout<< "===============================================================================" << std::endl;
        std::cout<< "1. Mesh Generator" << std::endl;
        std::cout<< "2. Particle Generator" << std::endl;
        std::cout<< "Select desired funtion (1/2): "; std::cin>> prog_func; std::cout<< std::endl;
        if (prog_func == 1)
        {
            mpm_mesh_main();
        }
        if (prog_func == 2)
        {
            mpm_particle_main();
        }
        std::cout<< "DONE" << std::endl;
        std::cin.get();
        std::cout<< "Generate another file? (Y/n)" << std::endl;
        std::cin >> stats;
        status = (stats == 'y' || stats == 'Y');
    }
}