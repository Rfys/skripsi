#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

#include "header/coord.h"
#include "header/functions.h"

std::vector<coordinates> transform_to_point(double& x, double& y, double& dl)
{
    std::vector<coordinates> point_list;
    point_list.reserve(4);
    point_list.emplace_back(coordinates(0, 0, 0));
    point_list.emplace_back(coordinates(x, 0, 0));
    point_list.emplace_back(coordinates(x, y, 0));
    point_list.emplace_back(coordinates(0, y, 0));
    return point_list;
}

//In circle, Z of input value is the angle
//x2 = R2 - y2
std::vector<coordinates> discretize_circle_segment(coordinates& first, coordinates& second, double dl)
{
    std::vector<coordinates> result;
    const double pi = 3.1415;
    double angle_rad = first.z*pi/180;
    double dx2 = (second.x - first.x)*(second.x - first.x);
    double dy2 = (second.y - first.y)*(second.y - first.y);
    double R2 = (dx2 + dy2)/(2*(1-cos(angle_rad)));
    double maks  = std::max(first.y, second.y);
    double minim = std::min(first.y, second.y);
    for (double i = 0; i < maks + (0.01*dl); i+=dl)
    {
        if (i >= minim)
        {
            double x = sqrt(R2 - i*i);
            result.push_back(coordinates(x, i, 0));
        }
    }
    return result;
}

//In Line, Z of input value is 0
//y = ax + b
std::vector<coordinates> discretize_line_segment(coordinates& first, coordinates& second, double dl)
{
    std::vector<coordinates> result;
    double dx = second.x - first.x;
    double dy = second.y - first.y;
    double maks  = std::max(first.y, second.y);
    double minim = std::min(first.y, second.y);
    if (dy == 0)
    {
        result.reserve(2);
        result.emplace_back(first);
        result.emplace_back(second);
    } else if (dx == 0)
    {
        for (double i = 0; i < maks + (0.01*dl); i+=dl)
        {
            if (i>=minim)
            {
                result.push_back(coordinates(first.x, i, 0));
            }
        }
    } else
    {
        double a = dy/dx;
        double b = first.y - (a*first.x);
        for (double i = 0; i < maks + (0.01*dl); i+=dl)
        {
            if (i >= minim)
            {
                double x = (i - b)/a;
                result.push_back(coordinates(x, i, 0));
            }
        }
    }
    return result;
}

/*Collecting all boundary Into 1 arraylist*/
std::vector<coordinates> shape_input(std::vector<coordinates>& input_pt, double& dl)
{
    input_pt.push_back(input_pt[0]);
    std::vector<coordinates> pt_sets;
    for (int i = 0; i < input_pt.size() - 1; i++)
    {
        std::vector<coordinates> a;
        if (input_pt[i].z != 0)
        {
            a = discretize_circle_segment(input_pt[i], input_pt[i+1], dl);
        } else  
        {
            a = discretize_line_segment(input_pt[i], input_pt[i+1], dl);
        } 
        for (int i = 0; i < a.size(); i++)
        {
            bool cek = true;
            for (int j = 0; j < pt_sets.size(); j++)
            {
                if (pt_sets[j] == a[i])
                {
                    cek = false;
                }
            }
            if (cek) pt_sets.push_back(a[i]);
        }
    }
    return pt_sets;
}

double get_max_y(std::vector<coordinates>& input_pt)
{
    double x = 0;
    for (int i = 0; i < input_pt.size(); i++)
    {
        if (x < input_pt[i].y)
        {
            x = input_pt[i].y;
        }
    }
    return x;
}

double get_max_x(std::vector<coordinates>& input_pt)
{
    double x = 0;
    for (int i = 0; i < input_pt.size(); i++)
    {
        if (x < input_pt[i].x)
        {
            x = input_pt[i].x;
        }
    }
    return x;
}

std::vector<std::vector<double>> transform_boundary(std::vector<coordinates>& input_pt, double& interval, double& limit)
{
    std::vector<std::vector<double>> index_and_boundary;
    for (double i = 0; i < limit + + (0.01*interval); i+= interval)
    {
        std::vector<double> tmp;
        tmp.push_back(0);
        for (int j = 0; j < input_pt.size(); j++)
        {
            if (i == input_pt[j].y)
            {
                tmp.push_back(input_pt[j].x);
            }     
        }
        std::sort(tmp.begin(),tmp.end());
        tmp[0]=i;
        index_and_boundary.push_back(tmp);
    }
    return index_and_boundary;
}

std::vector<coordinates>* generate_coordinate(std::vector<std::vector<double>>& index_and_boundary, double& z, double& dl, double& limit)
{
    std::vector<coordinates>* data_set = new std::vector<coordinates>;
    for (double k = 0; k < z + (0.01*dl); k+= dl)
    {
        for (int j = 0; j < index_and_boundary.size(); j++)
        {
            for (double i = 0; i < limit + (0.01*dl); i+=dl)
            {
                if (index_and_boundary[j].size()%2 == 1)
                {
                for (int n = 1; n < index_and_boundary[i].size(); n+=2)
                    {
                        if (i >= index_and_boundary[i][n] && i <= index_and_boundary[i][n+1])
                        {
                            (*data_set).push_back(coordinates(i, index_and_boundary[j][0], k));
                        }
                    }
                }
            }
        }
    }
    return data_set;
}

//std::vector<coordinates> generate_coordinate(double& x, double& y, double& z, int& n_cell_x, int& n_cell_y, int& n_cell_z, int& nnodes, int& ncells)
//{
//double dx, dy, dz;
////Calculate dx, dy, dz, n_cell_y, n_cell_z
//dx       = x/n_cell_x;
//n_cell_y = int(round(y/dx));
//n_cell_z = int(round(z/dx));
//dy      = y/(n_cell_y);
//dz      = z/(n_cell_z);
//if (n_cell_z == 0)
//{
//    dz   = 1;
//} if (n_cell_y == 0)
//{
//    dy   = 1;
//}
//
////calculate specs
//if (n_cell_z == 0)
//{
//    nnodes = (n_cell_x+1)*(n_cell_y+1);
//    ncells = n_cell_x*n_cell_y;
//    if (n_cell_y == 0)
//    {
//        nnodes = n_cell_x + 1;
//        ncells = n_cell_x;
//    }
//} else
//{
//    nnodes = (n_cell_x+1)*(n_cell_y+1)*(n_cell_z+1);
//    ncells = n_cell_x*n_cell_y*n_cell_z;
//}
//
////Set Coordinates to Initial Matrix
//std::vector<coordinates> data_set;
//data_set.reserve(nnodes);
//
//for (double i = 0; i <= z; i += dz)
//{
//    for (double j = 0; j <= y; j += dy)
//    {
//        for (double k = 0; k <= x; k += dx)
//        {
//            data_set.emplace_back(coordinates(k,j,i));
//        }
//    }
//}
//
////introduce Rotation
//double angle_deg, angle_rad;
//const float pi = 3.1415; 
//std::cout<< "Insert Rotation Angle (degree) [90 ~ -90]: "; std::cin>> angle_deg; std::cout << std::endl;
//angle_rad = angle_deg*pi/180;
//for (int i = 0; i < data_set.size(); i++)
//{
//    rotate(data_set[i], angle_rad);
//}
//
////introduce Translation
//double u, v, w;
//std::cout<< "Insert Translation Matrix [x <space> y <space> z] {0 0 0 for no-translation}: "; std::cin>> u >> v >> w; std::cout << std::endl;
//coordinates translation_matrix(u, v, w);
//for (int i = 0; i < data_set.size(); i++)
//{
//    translate(data_set[i], translation_matrix);
//}
//
//return data_set;
//}
//

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
