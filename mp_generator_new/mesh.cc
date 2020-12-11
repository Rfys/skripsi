#include "header/coord.h"
#include "header/functions.h"
#include <string>
#include <fstream>

void mpm_mesh_main()
{
    double x, y, z, dx;
    int n_cell_x = 0, n_cell_y = 0, n_cell_z = 0;
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

    auto input = transform_to_point(x, y, dx);
    for (int i = 0; i < input.size(); i++)
    {
        std::cout << input[i] << std::endl;
    }
    auto shape = shape_input(input, dx);
    for (int i = 0; i < shape.size(); i++)
    {
        std::cout << shape[i] << std::endl;
    }
    double max_y = get_max_y(input);
    double max_x = get_max_x(input);
    auto transformed = transform_boundary(shape, dx, max_y);
    for (int i = 0; i < transformed.size(); i++)
    {
        for (int j = 0; j < transformed[i].size(); j++)
        {
            std::cout << transformed[i][j] << " ";
        }
        std::cout<<"\n";
    }
    auto data_set = generate_coordinate(transformed, z, dx, max_x, n_cell_x, n_cell_y, n_cell_z); //ini pointer
    //auto node_set = generate_indices(n_cell_x, n_cell_y, n_cell_z);

    int nnodes, ncells;
    nnodes = (n_cell_x+1)*(n_cell_y+1)*(n_cell_z+1);
    ncells = (n_cell_x)*(n_cell_y)*(n_cell_z);
        
    //std::string filename;
    //std::cout<< "Insert File Name (eg. mesh.txt): "; std::cin >> filename; std::cout<< std::endl;
    
    //std::fstream mesh ("mesh.txt");

    //printout declaration
    std::cout << nnodes << " " << ncells << std::endl;
    //printout coordinates
    for (int i = 0; i < (*data_set).size(); i++)
    {
        std::cout << (*data_set)[i] << std::endl;
    }
    //printout indices
    //for (int i = 0; i < node_set.size(); i++)
    //{
    //    for (int j = 0; j < node_set[i].size() - 1; j++)
    //    {
    //        std::cout << node_set[i][j] << " ";
    //    }
    //    std::cout << node_set[i][node_set[i].size()-1] << std::endl;
    //}
    // std::cout.close();
    delete(data_set);
}