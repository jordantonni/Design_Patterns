#include <vector>
#include <string>
#include <iostream>

/*
 * ABSTRACT:
 * Because we can't overload constructors with the same parameters and types we can't differentiate
 * between cartessian and polar co-ordinates.
 * 
 * Therefore we must work around this by passing a third parameter to designate what co-ords we are using.
 * 
 * NOTE: Can't name the params x and y as we also accept polar radius and theta. Not descriptive.
 */

enum class CoordinateType
{
    CARTESIAN,
    POLAR
};

class Point
{
    float x;
    float y;

public:
    Point(float a, float b, CoordinateType co_ordinate_type = CoordinateType::CARTESIAN)
    {
        if (co_ordinate_type == CoordinateType::CARTESIAN){
            x = a;
            y = b;
        }
        else{
            x = a * cos(b);
            y = a * sin(b);
        }
    }
};

void test_NaivePoint()
{ }
