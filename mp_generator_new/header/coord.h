#pragma once
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

    bool is_equal(const coordinates& other) const
    {
        if (x == other.x && y == other.y && z == other.z) return true;
        else return false;    
    }

    bool operator==(const coordinates& other) const
    {
        return is_equal(other);
    }

    coordinates rotate(double& angle)
    {
        double cosine,  sine;
        cosine = cos(angle);
        sine   = sin(angle);
        coordinates row1(cosine, -sine, 0);
        coordinates row2(sine, cosine, 0);
        coordinates row3(0, 0, 1);

        double x = round((row1*(*this))*1000)/1000;
        double y = round((row2*(*this))*1000)/1000;
        double z = round((row3*(*this))*1000)/1000;

        return coordinates(x , y , z);
    }

    coordinates translate(double dx, double dy, double dz)
    {
        return coordinates(x + dx , y + dy , z + dz);
    }
};
