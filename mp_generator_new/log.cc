#include "header/coord.h"
#include <math.h>
#include <iostream>

std::ostream& operator<<(std::ostream& print, const coordinates& coordinates)
{
    print << coordinates.x << " " << coordinates.y << " " << coordinates.z;
    return print;
}