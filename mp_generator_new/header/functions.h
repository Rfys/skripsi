#pragma once
#include "coord.h"
#include <iostream>
#include <vector>

std::vector<coordinates> transform_to_point(double& x, double& y, double& dl);
std::ostream& operator<<(std::ostream& print, const coordinates& coordinates);
std::vector<coordinates> discretize_circle_segment(coordinates& first, coordinates& second, double dl);
std::vector<coordinates> discretize_line_segment(coordinates& first, coordinates& second, double dl);
std::vector<coordinates> shape_input(std::vector<coordinates>& input_pt, double& dl);
double get_max_y(std::vector<coordinates>& input_pt);
double get_max_x(std::vector<coordinates>& input_pt);
std::vector<std::vector<double>> transform_boundary(std::vector<coordinates>& input_pt, double& interval, double& limit);
std::vector<coordinates>* generate_coordinate(std::vector<std::vector<double>>& index_and_boundary, double& z, double& dl, double& limit, int& nx, int& ny, int& nz);
std::vector<std::vector<int>> generate_indices(int n_cell_x, int n_cell_y, int n_cell_z);

void mpm_mesh_main();
void mpm_particle_main();