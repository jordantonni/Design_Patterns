#include <string>
#include <iostream>
#include <sstream>
#include <stdint.h>
using namespace std;

/*
 * ABSTRACT:
 * Wrapping class decorator has problems. Specificly it inherits from the base and not the more specific type that we may be decorating.
 * Therefore it doesnt get the interface from the specific type.
 * 
 * Mix-in allows us to inherit from a templated type we pass to the class. So we are able to decorate (wrap and add more functionality) to the class passed in
 * while also getting all its interface as we inherit from it and some form a ARE-A relationaship.
 * 
 * Basically. Mix-in inheritance allows us to inherit from a templated type. Get their functionality by virtue of the inheritance and then add more to it
 * / decorate the class by specializing.
 */

struct Shape
{
    virtual string str() = 0;
};

struct Circle : Shape
{
    float radius;

    // This default constructor is required because the mix-in templated decorator will need to call some constructor of the 
    // class it is inheritating from / decorating. Can't call the full constructor easily as it will be different for any type T.
    // Could get round this by some fancy meta-programming, but fuck that.

    //This is fixed in the improvements by templating the constructor with variadic template and unpacking the args to the T::T() construtor.
    Circle() {}

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

/*
 * We inherit from the class we are using for the template
 */
template <typename T>
struct ColouredMixinShape : T
{
    string color;

    explicit ColouredMixinShape(const string& color)
        : color{ color }
    {}

    string str() override
    {
        stringstream ss;
        ss << T::str() << " has color " << color;
        return ss.str();
    }
};


void test_mixin_decorator()
{
    ColouredMixinShape<Circle> ms { "Red" };
    ms.radius = 6;
    cout << ms.str() << endl;
}
