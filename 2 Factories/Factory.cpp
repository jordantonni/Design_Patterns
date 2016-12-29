#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
using namespace std;

/*
 * ABSTRACT:
 * If the factory methods become large or complicated.
 * We create a new class, called a Factory, that houses the static factory methods and creates the objects needed.
 * 
 * Keeping the constructor private, we make the Factory class a friend. Giving access to the constructor.
 */

class Point
{
    float x;
    float y;
    Point(float x, float y)

        : x{ x }
        , y{ y }
    {}

public:
    friend std::ostream& operator<<(std::ostream& os, const Point& obj)
    {
        return os
                << "x: " << obj.x
                << " y: " << obj.y;
    }

    friend class PointFactory;
};

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

void test_Factory()
{
    auto c = PointFactory::NewCartesian(0, 4);
    auto po = PointFactory::NewPolar(float(5), float(M_PI_4));


    cout << c << endl;
    cout << po << endl;
}
