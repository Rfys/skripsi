#include "header/coord.h"
#include "header/functions.h"
#include <string>
#include <fstream>

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
    double x, y, z, dx;
    int counter;
    std::vector<coordinates> input;

    std::cout<< "Insert Total Shape Points: "; std::cin >> counter; std::cout << std::endl;
    input.reserve(counter);
    for (int i = 0; i < counter; i++)
    {
        double m, n, o;
        std::cout << "Insert point " << i << "[x y z]: "; std::cin >> m >> n >> o; std::cout << std::endl;
        input.emplace_back(coordinates(m, n, o));
    }

    std::cout<< "Insert Particle spacing: "; std::cin >> dx; std::cout << std::endl;

    auto shape = shape_input(input, dx);

    for (int i = 0; i < shape.size(); i++)
    {
        std::cout << shape[i] << std::endl;
    }
    std::cout << std::endl;
    
    double max_y = get_max_y(input);
    double max_x = get_max_x(input);
    
    std::cout << max_y << " " << max_x << std::endl << "here\n\n";

    auto transformed = transform_boundary(shape, dx, max_y);
    for (int i = 0; i < transformed.size(); i++)
    {
        for (int j = 0; j < transformed[i].size(); j++)
        {
            std::cout << transformed[i][j] << " ";
        }
        std::cout<<"\n";
    }

    std::cout << std::endl;
    std::cout <<"here\n";
    auto data_set = generate_coordinate(transformed, z, dx, max_x); //ini pointer

    //introduce Rotation
    {
        double angle_deg;
        std::cout<< "Insert Rotation Angle (degree) [90 ~ -90]: "; std::cin>> angle_deg; std::cout << std::endl;
        for (int i = 0; i < (*data_set).size(); i++)
        {
            (*data_set)[i] = (*data_set)[i].rotate(angle_deg);
        }
    }

    //introduce Translation
    {
        double u, v, w;
        std::cout<< "Insert Translation Matrix [x <space> y <space> z] {0 0 0 for no-translation}: "; std::cin>> u >> v >> w; std::cout << std::endl;
        for (int i = 0; i < (*data_set).size(); i++)
        {
            (*data_set)[i] = (*data_set)[i].translate(u, v, w);
        }
    }

    //std::string filename;
    //std::cout<< "Insert File Name (eg. mesh.txt): "; std::cin >> filename; std::cout<< std::endl;
    std::ofstream particles ("generated/particles.txt");

    //printout declaration
    particles << (*data_set).size() << std::endl;
    //printout coordinates
    for (int i = 0; i < (*data_set).size(); i++)
    {
        particles << (*data_set)[i] << std::endl;
    }

    particles.close();
    delete(data_set);
}