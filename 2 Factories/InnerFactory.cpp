#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
using namespace std;

/*
 * ABSTRACT:
 * We create a Factory class as an inner class of the object we are creating.
 * 
 * This tightens the API in that it shows the PointFactory really is only there to support the Point class.
 * Static member object of PointFactory provides the access to the Factory.
 */

class Point
{
    float x;
    float y;

    Point(float x, float y)

        : x{ x }
        , y{ y }
    {}

    //Inner private factory class
    //Note: No reason to only return a Point object by value. We could be returning unique_ptrs or abstract interfaces
    class PointFactory
    {
    public:
        static Point NewCartesian(const float x, const float y)
        {
            return { x,y };
        }

        static Point NewPolar(const float radius, const float theta)
        {
            return { radius * cos(theta),
                    radius * sin(theta) };
        }
    };

public:
    friend std::ostream& operator<<(std::ostream& os, const Point& obj)
    {
        return os
                << "x: " << obj.x
                << " y: " << obj.y;
    }

    static PointFactory Factory;
};


void test_InnerFactory()
{
    auto c = Point::Factory.NewCartesian(0, 4);
    auto po = Point::Factory.NewPolar(float(5), float(M_PI_4));


    cout << c << endl;
    cout << po << endl;
}
