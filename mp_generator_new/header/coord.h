#pragma once
#include <math.h>
#include <iostream>

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

    bool is_equal(const coordinates& other) const
    {
        if (x == other.x && y == other.y && z == other.z) return true;
        else return false;    
    }

    bool operator==(const coordinates& other) const
    {
        return is_equal(other);
    }

    coordinates rotate(const double& angle_deg)
    {
        double cosine, sine, angle_rad;
        const float pi = 3.1415; 
        angle_rad = angle_deg*pi/180; 
        cosine = cos(angle_rad);
        sine   = sin(angle_rad);
        coordinates row1(cosine,  -sine,     0);
        coordinates row2(sine  , cosine,     0);
        coordinates row3(0     ,      0,     1);

        double nx = round((row1*(*this))*1000)/1000;
        double ny = round((row2*(*this))*1000)/1000;
        double nz = round((row3*(*this))*1000)/1000;
    
        return coordinates(nx, ny, nz);
    }

    coordinates translate(const double& dx, const double& dy, const double& dz) const
    {
        return coordinates(x + dx , y + dy , z + dz);
    }
};
