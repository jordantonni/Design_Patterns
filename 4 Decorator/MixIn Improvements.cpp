#include <string>
#include <iostream>
#include <sstream>
#include <stdint.h>
using namespace std;

/*
 * ABSTRACT:
 * Static assert(is_base_of) within the mix-in inheritance decorator, ensures we only decorate the type of classes we are aiming to.
 *
 * Get rid of
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


template <typename T>
struct ColouredMixinShape : T
{
    // Here we ensure that you cant just pass any class in as a template parameter
    // It must be a shape class!
    static_assert(is_base_of<Shape, T>::value, " Template argument must be a Shape");


    string color;

    /*
     * Template the decorator constructor by adding variadic arguments. Then pass these unpacked to the templated types constructor.
     * This allows us to remove the default constructors for the circle class etc.
     */
    template <typename... Args>
    explicit ColouredMixinShape(const string& color, Args ... args)
        : T::T(args...)
        , color{ color }
    {}

    string str() override
    {
        stringstream ss;
        ss << T::str() << " has color " << color;
        return ss.str();
    }
};


void test_mixin_decorator_improvements()
{
    ColouredMixinShape<Circle> ms { "Red" , 24};
    cout << ms.str() << endl;
}
