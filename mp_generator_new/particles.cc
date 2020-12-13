#include <iostream>
#include "header/coord.h"
#include "header/functions.h"

//double x,y,z;
//int n_cell_x, n_cell_y, n_cell_z;
//int nparticles, ncells, n;
//std::vector<coordinates> coordinate;
//std::vector<std::vector<int>> indices;
//std::cout<< "                         ____________________                        " << std::endl;
//std::cout<< "                        /                   /|                       " << std::endl;
//std::cout<< "                       /                   / |                       " << std::endl;
//std::cout<< "                      /__________________ /  | Y                     " << std::endl;
//std::cout<< "                      |                  |   |                       " << std::endl;
//std::cout<< "                      |                  |   |                       " << std::endl;
//std::cout<< "                      |                  |  /                        " << std::endl;
//std::cout<< "                      |                  | / Z                       " << std::endl;
//std::cout<< "                      |__________________|/                          " << std::endl;
//std::cout<< "                               X                                     " << std::endl;
//std::cout<< "Insert X: "; std::cin>> x; std::cout<< std::endl;
//std::cout<< "Insert Y: "; std::cin>> y; std::cout<< std::endl;
//std::cout<< "Insert Z: "; std::cin>> z; std::cout<< std::endl;
//std::cout<< "Insert Number of Particles in X direction: "; std::cin>> n; std::cout<< std::endl;
//n_cell_x = n - 1;
//coordinate  = generate_coordinate(x, y, z, n_cell_x, n_cell_y, n_cell_z, nparticles, ncells
//std::ofstream particles ("particles.txt");
////printout declaration
//particles << nparticles << std::end
////printout coordinates
//for (int i = 0; i < coordinate.size(); i++)
//{
//    particles << coordinate[i] << std::endl;
//}
//particles.close();

void mpm_particle_main()
{
    double x, y, z, angle;
    std::cout << "Insert Coordinate"; std::cin >> x >> y >> z; std::cout<< std::endl;
    std::cout << "Insert Angle"; std::cin >> angle; std::cout<< std::endl;
    coordinates test = coordinates(x, y, z);
    test = test.translate(angle, angle, angle);
    std::cout << test << std::endl;
    std::cin.get();
}