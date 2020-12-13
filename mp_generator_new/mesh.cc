#include "header/coord.h"
#include "header/functions.h"
#include <string>
#include <fstream>

void mpm_mesh_main()
{
    double x, y, z, dx;
    
    std::vector<coordinates> coordinate;
    std::vector<std::vector<int>> indices;
    std::cout<< "                         ____________________                        " << std::endl;
    std::cout<< "                        /                   /|                       " << std::endl;
    std::cout<< "                       /                   / |                       " << std::endl;
    std::cout<< "                      /__________________ /  | Y                     " << std::endl;
    std::cout<< "                      |                  |   |                       " << std::endl;
    std::cout<< "                      |                  |   |                       " << std::endl;
    std::cout<< "                      |                  |  /                        " << std::endl;
    std::cout<< "                      |                  | / Z                       " << std::endl;
    std::cout<< "                      |__________________|/                          " << std::endl;
    std::cout<< "                               X                                     " << std::endl;
    std::cout<< "Insert X: "; std::cin>> x; std::cout<< std::endl;
    std::cout<< "Insert Y: "; std::cin>> y; std::cout<< std::endl;
    std::cout<< "Insert Z: "; std::cin>> z; std::cout<< std::endl;
    std::cout<< "Insert Cell Length: "; std::cin>> dx; std::cout<< std::endl;

    auto input = transform_to_point(x, y);
    for (int i = 0; i < input.size(); i++)
    {
        std::cout << input[i] << std::endl;
    }

    std::cout << std::endl;
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

    int nnodes, ncells;
    int n_cell_x = 0, n_cell_y = 0, n_cell_z = 0;
    int n_node_x = 0, n_node_y = 0, n_node_z = 0;
    n_cell_x = int(floor(x/dx));
    n_cell_y = int(floor(y/dx));
    n_cell_z = int(floor(z/dx));
    auto node_set = generate_indices(n_cell_x, n_cell_y, n_cell_z);
    if (n_cell_x == 0) n_cell_x = 1;
    if (n_cell_y == 0) n_cell_y = 1;
    if (n_cell_z == 0) n_cell_z = 1;
    n_node_x = int(floor(x/dx)) + 1;
    n_node_y = int(floor(y/dx)) + 1;
    n_node_z = int(floor(z/dx)) + 1;
    ncells = (n_cell_x)*(n_cell_y)*(n_cell_z);
    nnodes = (n_node_x)*(n_node_y)*(n_node_z);

    //std::string filename;
    //std::cout<< "Insert File Name (eg. mesh.txt): "; std::cin >> filename; std::cout<< std::endl;
    std::ofstream mesh ("generated/mesh.txt");

    //printout declaration
    mesh << nnodes << " " << ncells << std::endl;
    //printout coordinates
    for (int i = 0; i < (*data_set).size(); i++)
    {
        mesh << (*data_set)[i] << std::endl;
    }

    // printout indices
    for (int i = 0; i < node_set.size(); i++)
    {
        for (int j = 0; j < node_set[i].size() - 1; j++)
        {
            mesh << node_set[i][j] << " ";
        }
        mesh << node_set[i][node_set[i].size()-1] << std::endl;
    }
    mesh.close();
    
    delete(data_set);
}