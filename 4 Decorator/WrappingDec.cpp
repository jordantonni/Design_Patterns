#include <string>
#include <iostream>
#include <sstream>
#include <stdint.h>
using namespace std;

/*
 * ABSTRACT:
 *  Wrapping decorator pattern for classes allows us to add traits to classes without having to interfere with base class or hierercy of the classes.
 * 
 * NOTE:
 *  The decorator classes store a refernce to the base class of Shape.
 *  Therefore, if each decorator themselves inherites from Shape, we can decorate a decorator and chain them.
 *  
 * PROBLEMS:
 * To decorate a concrete shape, such as a circle or square, we need to create one of them first then pass it to the decorator.
 * The decorators inherit from the base shape class, and also aggregate a shape by reference and while this lets us chain decorators,
 * it means if we add functionality to the concrete circle class, a circle decorator doesnt get that new functionality as it doesnt inherit from the
 * circle, only the base.
 */

struct Shape
{
    virtual string str() = 0;
};

struct Circle : Shape
{
    float radius;

    explicit Circle(const float rad)
        : radius { rad }
    {}

    string str() override
    {
        stringstream ss;
        ss << "A circle of radius: " << radius;
        return ss.str();
    }
};

struct Square : Shape
{
    float side;

    explicit Square(float side)
        : side { side }
    {}

    string str() override
    {
        stringstream ss;
        ss << "A square with side length: " << side;
        return ss.str();
    }
};

/*
 * This class is the decorator.
 * It wraps the Shape object by taking a reference to it and adding some more details to it.
 * 
 * Note: It implements the same str() function shape has and does a function decorator around it.
 */
struct ColoredShape : Shape
{
    Shape& shape;
    string color;

    ColoredShape(Shape& shape, const string& color)
        : shape{ shape }
        , color{ color }
    {}


    string str() override
    {
        ostringstream oss;
        oss << shape.str() << "has color " << color;
        return oss.str();
    }
};

struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t trans;


    TransparentShape(Shape& shape, uint8_t trans)
        : shape{ shape }
        , trans{ trans }
    {}


    string str() override
    {
        ostringstream oss;
        oss << shape.str() << " is " << (float(trans) / UINT8_MAX) * 100 << "% transparent";
        return oss.str();
    }
};

void test_wrapping_decorator()
{
    Circle c1 { 5 };
    cout << c1.str() << endl;

    ColoredShape cs { c1, "Green" };
    cout << endl << cs.str() << endl;

    // Decorates the ColouredShape Decorator, which in turn decorates the Circle class.
    TransparentShape ts{cs, 128};
    cout << endl << ts.str() << endl;

} 