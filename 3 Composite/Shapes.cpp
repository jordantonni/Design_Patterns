#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * ABSTRACT:
 * Uniform draw interface is supplied by both the single object (Circle) and the composite object (Group)
 * 
 * This allows us to treat both in the same way thought that API.
 * 
 * What allows this to happen?:
 *      1) Both single and composite implement the same interface, which defines the uniform API to use.
 *      2) Composite class is compositied with a vector of objects that inherit this interface. Allows us to iterate through each 
 *          contained object and call their API.
 */

struct GeometricObject
{
    virtual void draw() = 0;
};

struct Circle : GeometricObject
{
    void draw() override
    {
        cout << "Drawing Circle" << endl;
    }
};

struct Group : GeometricObject
{
    string name;
    vector<GeometricObject*> objects; // Allows for group of groups, also of circle etc.

    Group(const string& name)
        : name{ name }
    {}

    void draw() override
    {
        cout << "Drawing group " << name.c_str() << " contains : " << endl;
        for (auto& x : objects)
            x->draw();
    }

    void add_to_group(GeometricObject* obj)
    {
        objects.emplace_back(obj);
    }
};

void test_shapes()
{
    Circle c1, c2;
    Group g1{"Group 1"};
    g1.add_to_group(&c1);

    Group g2{"Group 2"};
    g2.add_to_group(&c2);

    g1.add_to_group(&g2);

    g1.draw();
}
