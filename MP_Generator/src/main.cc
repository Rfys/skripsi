#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

std::ofstream mesh("mesh.txt");

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
};

std::ostream& operator<<(std::ostream& print, const coordinates& coordinates)
{
    print << coordinates.x << " " << coordinates.y << " " << coordinates.z;
    return print;
}

void rotate(coordinates& object, double& angle)
{
    coordinates tmp(0,0,0);
    double cosine,  sine;
    cosine = cos(angle);
    sine   = sin(angle);
    // std::cout<< cosine << " ******** " <<sine << std::endl;
    coordinates row1(cosine, -sine, 0);
    coordinates row2(sine, cosine, 0);
    coordinates row3(0, 0, 1);
    // std::cout<< row1 << std::endl << row2 << std::endl << row3 << std::endl;
    // std::cin.get();

    tmp.x = round((row1*object)*1000)/1000;
    tmp.y = round((row2*object)*1000)/1000;
    tmp.z = round((row3*object)*1000)/1000;

    object = tmp;
}

// coordinates translate(coordinates& object, double& dx, double& dy)

void generate_coordinate(double& x, double& y, double& z, int& n_cell_x, int& n_cell_y, int& n_cell_z, double& dx, double& dy, double& dz)
{
//Calculate dx, dy, dz, n_cell_y, n_cell_z
dx       = x/n_cell_x;
n_cell_y = int(round(y/dx));
n_cell_z = int(round(z/dx));
dy       = y/(n_cell_y);
if (n_cell_z == 0)
{
    dz   = 1;
} else
{
    dz    = z/(n_cell_z);
}

//printout specs
int nnodes, ncells;
if (n_cell_z == 0)
{
    nnodes = (n_cell_x+1)*(n_cell_y+1);
    ncells = n_cell_x*n_cell_y;
} else
{
    nnodes = (n_cell_x+1)*(n_cell_y+1)*(n_cell_z+1);
    ncells = n_cell_x*n_cell_y*n_cell_z;
}

// std::cout<< dx << " "<< dy << " "<< dz << " "<< n_cell_x << " "<< n_cell_y << " "<< n_cell_z << std::endl; 

//Set Coordinates to Initial Matrix
std::vector<coordinates> data_set;
data_set.reserve(nnodes);

for (double i = 0; i < z + dz; i += dz)
{
    for (double j = 0; j < y + dy; j += dy)
    {
        for (double k = 0; k < x + dx; k += dx)
        {
            data_set.emplace_back(coordinates(k,j,i));
        }
    }
}

//introduce Rotation
double angle_deg, angle_rad;
const float pi = 3.1415; 
std::cout<< "Insert Rotation Angle (degree) [90 ~ -90]: "; std::cin>> angle_deg; std::cout<< std::endl;
angle_rad = angle_deg*pi/180;
for (int i = 0; i < data_set.size(); i++)
{
    rotate(data_set[i], angle_rad);
}

//introduce Translation


//printout coordinates

mesh<< nnodes << " " << ncells << std::endl;
for (int i = 0; i < nnodes; i++)
{
    mesh<< data_set[i]  << std::endl;
}

}

void generate_indices(int n_cell_x, int n_cell_y, int n_cell_z)
{
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
                    int index[8];
                    index[0]=n_node_y*n_node_x*k + n_node_x*j + i;
                    index[1]=index[0]+1;
                    index[2]=index[1]+n_node_x;
                    index[3]=index[0]+n_node_x;
                    index[4]=index[0]+n_node_x*n_node_y*k;
                    index[5]=index[1]+n_node_x*n_node_y*k;
                    index[6]=index[2]+n_node_x*n_node_y*k;
                    index[7]=index[3]+n_node_x*n_node_y*k;
                    
                    for (int n = 0; n < 7; n++)
                    {
                        mesh << index[n] << " ";
                    }
                    mesh << index[7] << std::endl;
                    
                }
            }
        }
        
    } else
    {
     for (int j = 0; j < n_cell_y; j++)
        {
            for (int i = 0; i < n_cell_x; i++)
            {
                int index[4];
                index[0]=n_node_x*j + i;
                index[1]=index[0]+1;
                index[2]=index[1]+n_node_x;
                index[3]=index[0]+n_node_x;
                
                for (int n = 0; n < 3; n++)
                {
                    mesh<< index[n] << " ";
                }
                mesh<< index[3] << std::endl;
                
            }
        }   
    }
}

int main()
{
    double x,y,z,dx,dy,dz;
    int n_cell_x, n_cell_y, n_cell_z;

    std::cout<< "=====================================================================" << std::endl;
    std::cout<< "+       Mesh and Particle Generating Program (for CB-Geo MPM)       +" << std::endl;
    std::cout<< "+                    Quadrilateral & Hexahedron                     +" << std::endl;
    std::cout<< "=====================================================================" << std::endl;
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

    
    //std::freopen("mesh.txt", "w", stdout);
    generate_coordinate(x, y, z, n_cell_x, n_cell_y, n_cell_z, dx, dy, dz);
    generate_indices(n_cell_x, n_cell_y, n_cell_z);
    //std::freopen("CON", "w", stdout);
    
    std::cout<< "DONE" << std::endl;
    std::cin.get();
}
