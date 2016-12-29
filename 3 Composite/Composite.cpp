#include <vector>
#include <iostream>
#include <memory>
using namespace std;
/*
 * ABSTRACT:
 * Problems we encounted when using composition and unification of interfaces between single objects and compositie objects.
 * Single object = Literal
 * Compositie object = AdditionExpression
 * 
 * Problem:
 * How do we traverse all the contained objects.
 * 
 * Solution:
 * Vistor pattern. Each class overrides the collect method that takes in a vector reference.
 * Objects add their contained values to the vector.
 * 
 */

struct Expression
{
    virtual double eval() = 0;
    virtual void collect(vector<double>& v) = 0;
};

// Single object that models one value.
// Every expression will be reduced down to this.
struct Literal : Expression
{
    double value;

    explicit Literal(double value)
        : value{ value }
    {}

    double eval() override
    {
        return value;
    }


    void collect(vector<double>& v) override
    {
        v.emplace_back(value);
    }
};

// Composite object models additon of two sub expressions.
struct AdditionExpression : Expression
{
    Expression *left, *right;

    AdditionExpression(Expression* left, Expression* right)
        : left{ left }
        , right{ right }
    {}

    double eval() override
    {
        return left->eval() + right->eval();
    }


    void collect(vector<double>& v) override
    {
        left->collect(v);
        right->collect(v);
    }
};

void test_composite()
{
    AdditionExpression sub {
        new Literal{ 5 },
        new AdditionExpression{
            new Literal{ 9 },
            new Literal{ 1 }
            }
        };

    cout << sub.eval() << endl;

    vector<double> vec;
    sub.collect(vec);
    for(auto& v : vec)
        cout << v << endl;

}
