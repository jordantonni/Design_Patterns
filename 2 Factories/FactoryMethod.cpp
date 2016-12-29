#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
using namespace std;

/*
 * ABSTRACT:
 * Constructor is made private. Only invoked via the factory methods.
 * 
 * Factory methods are static to the class. More descriptive of the instantiation they provide.
 */

class Point
{
public:
    Point(float x, float y)
        : x{ x }
        , y{ y }
    {}

    float x;
    float y;

    // Factory methods. Better describe how object is created.
    // Note: Using uniform initialization to pass an initializer list to the private constructor.
    static Point NewCartesian(const float x, const float y)
    {
        return { x,y };
    }

    static Point NewPolar(const float radius, const float theta)
    {
        return { radius * cos(theta),
                radius * sin(theta) };
    }


    friend std::ostream& operator<<(std::ostream& os, const Point& obj)
    {
        return os
                << "x: " << obj.x
                << " y: " << obj.y;
    }
};

void test_FactoryMethod()
{
    Point p { 1,2 };
    auto c = Point::NewCartesian(0, 4);
    auto po = Point::NewPolar(float(5), float(M_PI_2));


    cout << p << endl;
    cout << c << endl;
    cout << po << endl;
}
