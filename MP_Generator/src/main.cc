#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

struct coordinates
{
    double x, y, z;

    coordinates(double x, double y, double z)
        : x(x), y(y), z(z) {}
    
    double dot_product(const coordinates& other) const
    {
        return (x*other.x + y*other.y + z*other.z);
    }

    double operator*(const coordinates& other) const
    {
        return dot_product(other);
    }

    coordinates add(const coordinates& other) const
    {
        return coordinates(x + other.x , y + other.y , z + other.z);
    }

    coordinates operator+(const coordinates& other) const
    {
        return add(other);
    }
};

void rotate(coordinates& object, double& angle)
{
    coordinates tmp(0,0,0);
    double cosine,  sine;
    cosine = cos(angle);
    sine   = sin(angle);
    coordinates row1(cosine, -sine, 0);
    coordinates row2(sine, cosine, 0);
    coordinates row3(0, 0, 1);

    tmp.x = round((row1*object)*1000)/1000;
    tmp.y = round((row2*object)*1000)/1000;
    tmp.z = round((row3*object)*1000)/1000;

    object = tmp;
}

void translate(coordinates& object, coordinates& translator)
{
    object = object + translator;
}

std::ostream& operator<<(std::ostream& print, const coordinates& coordinates)
{
    print << coordinates.x << " " << coordinates.y << " " << coordinates.z;
    return print;
}

std::vector<coordinates> generate_coordinate(double& x, double& y, double& z, int& n_cell_x, int& n_cell_y, int& n_cell_z, int& nnodes, int& ncells)
{
double dx, dy, dz;
//Calculate dx, dy, dz, n_cell_y, n_cell_z
dx       = x/n_cell_x;
n_cell_y = int(round(y/dx));
n_cell_z = int(round(z/dx));
dy      = y/(n_cell_y);
dz      = z/(n_cell_z);
if (n_cell_z == 0)
{
    dz   = 1;
} if (n_cell_y == 0)
{
    dy   = 1;
}


//calculate specs
if (n_cell_z == 0)
{
    nnodes = (n_cell_x+1)*(n_cell_y+1);
    ncells = n_cell_x*n_cell_y;
    if (n_cell_y == 0)
    {
        nnodes = n_cell_x + 1;
        ncells = n_cell_x;
    }
} else
{
    nnodes = (n_cell_x+1)*(n_cell_y+1)*(n_cell_z+1);
    ncells = n_cell_x*n_cell_y*n_cell_z;
}

//Set Coordinates to Initial Matrix
std::vector<coordinates> data_set;
data_set.reserve(nnodes);

for (double i = 0; i <= z; i += dz)
{
    for (double j = 0; j <= y; j += dy)
    {
        for (double k = 0; k <= x; k += dx)
        {
            data_set.emplace_back(coordinates(k,j,i));
        }
    }
}

//introduce Rotation
double angle_deg, angle_rad;
const float pi = 3.1415; 
std::cout<< "Insert Rotation Angle (degree) [90 ~ -90]: "; std::cin>> angle_deg; std::cout << std::endl;
angle_rad = angle_deg*pi/180;
for (int i = 0; i < data_set.size(); i++)
{
    rotate(data_set[i], angle_rad);
}

//introduce Translation
double u, v, w;
std::cout<< "Insert Translation Matrix [x <space> y <space> z] {0 0 0 for no-translation}: "; std::cin>> u >> v >> w; std::cout << std::endl;
coordinates translation_matrix(u, v, w);
for (int i = 0; i < data_set.size(); i++)
{
    translate(data_set[i], translation_matrix);
}

return data_set;
}

std::vector<std::vector<int>> generate_indices(int n_cell_x, int n_cell_y, int n_cell_z)
{
    std::vector<std::vector<int>> data_set;
    int n_node_x = n_cell_x + 1;
    int n_node_y = n_cell_y + 1;
    int n_node_z = n_cell_z + 1;
    if (n_cell_z > 0)
    {
        for (int k = 0; k < n_cell_z; k++)
        {
              for (int j = 0; j < n_cell_y; j++)
            {
                for (int i = 0; i < n_cell_x; i++)
                {
                    std::vector<int> index;
                    index.reserve(8);
                    index.emplace_back(n_node_y*n_node_x*k + n_node_x*j + i);
                    index.emplace_back(index[0]+1);
                    index.emplace_back(index[1]+n_node_x);
                    index.emplace_back(index[0]+n_node_x);
                    index.emplace_back(index[0]+n_node_x*n_node_y);
                    index.emplace_back(index[1]+n_node_x*n_node_y);
                    index.emplace_back(index[2]+n_node_x*n_node_y);
                    index.emplace_back(index[3]+n_node_x*n_node_y);
                    data_set.push_back(index);
                }
            }
        }
    } else if (n_cell_y > 0)
    {
        for (int j = 0; j < n_cell_y; j++)
        {
            for (int i = 0; i < n_cell_x; i++)
            {
                std::vector<int> index;
                index.reserve(4);
                index.emplace_back(n_node_x*j + i);
                index.emplace_back(index[0]+1);
                index.emplace_back(index[1]+n_node_x);
                index.emplace_back(index[0]+n_node_x);
                data_set.push_back(index);
            }
        }   
    } else
    {
        for (int i = 0; i < n_cell_x; i++)
        {
            std::vector<int> index;
            index.reserve(2);
            index.emplace_back(i);
            index.emplace_back(i+1);
            data_set.push_back(index);
        }
        
    }
    
    
    return data_set;
}

int main()
{
    bool status = true;
    int prog_func;
    char stats;
    while (status)
    {
        std::cout<< "=====================================================================" << std::endl;
        std::cout<< "+       Mesh and Particle Generating Program (for CB-Geo MPM)       +" << std::endl;
        std::cout<< "+                    Quadrilateral & Hexahedron                     +" << std::endl;
        std::cout<< "=====================================================================" << std::endl;
        std::cout<< "1. Mesh Generator" << std::endl;
        std::cout<< "2. Particle Generator" << std::endl;
        std::cout<< "Select desired funtion (1/2): "; std::cin>> prog_func; std::cout<< std::endl;
        if (prog_func == 1)
        {
            double x,y,z;
            int n_cell_x, n_cell_y, n_cell_z;
            int nnodes, ncells;
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
            std::cout<< "Insert Number of Cells in X direction: "; std::cin>> n_cell_x; std::cout<< std::endl;
            coordinate  = generate_coordinate(x, y, z, n_cell_x, n_cell_y, n_cell_z, nnodes, ncells);
            indices     = generate_indices(n_cell_x, n_cell_y, n_cell_z);

            std::ofstream mesh ("mesh.txt");
            //printout declaration
            mesh << nnodes << " " << ncells << std::endl;

            //printout coordinates
            for (int i = 0; i < coordinate.size(); i++)
            {
                mesh << coordinate[i] << std::endl;
            }

            //printout indices
            for (int i = 0; i < indices.size(); i++)
            {
                for (int j = 0; j < indices[i].size() - 1; j++)
                {
                    mesh << indices[i][j] << " ";
                }
                mesh << indices[i][indices[i].size()-1] << std::endl;
            }
            mesh.close();
        }
        if (prog_func == 2)
        {
            double x,y,z;
            int n_cell_x, n_cell_y, n_cell_z;
            int nparticles, ncells, n;
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
            std::cout<< "Insert Number of Particles in X direction: "; std::cin>> n; std::cout<< std::endl;
            n_cell_x = n - 1;
            coordinate  = generate_coordinate(x, y, z, n_cell_x, n_cell_y, n_cell_z, nparticles, ncells);

            std::ofstream particles ("particles.txt");
            //printout declaration
            particles << nparticles << std::endl;

            //printout coordinates
            for (int i = 0; i < coordinate.size(); i++)
            {
                particles << coordinate[i] << std::endl;
            }
            particles.close();
        }
        std::cout<< "DONE" << std::endl;
        std::cin.get();
        std::cout<< "Generate another file? (Y/n)" << std::endl;
        std::cin >> stats;
        status = (stats == 'y' || stats == 'Y');
    }
}

/*
To Do List :
1. 3D node indices
2. 
*/
