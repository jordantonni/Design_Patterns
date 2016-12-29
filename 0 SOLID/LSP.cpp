#include "stdafx.h"
#pragma once

using namespace std;

class Rectangle
{
protected:
    int height;
    int width;

public:

    explicit Rectangle(int height, int width)
        : height(height)
        , width(width) {}

    virtual ~Rectangle() {}

    virtual int GetHeight() const
    {
        return height;
    }

    virtual void SetHeight(const int height)
    {
        this->height = height;
    }

    virtual int GetWidth() const
    {
        return width;
    }

    virtual void SetWidth(const int width)
    {
        this->width = width;
    }

    int Area() const
    {
        return width * height;
    }
};

/*
 * Violates the Liskov Substitution Principle: Subtypes should be able to replace their base types
 *  in any area of the program without changing the program correctness.
 *  
 *  Square violates this by having its SetHeight and SetWidth methods change both dimenions, 
 *  this breaks the correctness of the process() function.
 *  
 *  FIX: Have a factory of Rectangle than is able to create a Square, without needed to make a square subclass.
 *       
 */
class Square : public Rectangle
{
public:
    explicit Square(int size)
        : Rectangle(size, size) {}

    void SetHeight(const int height) override
    {
        this->height = width = height;
    }

    void SetWidth(const int width) override
    {
        this->width = height = width;
    }
};


void process(Rectangle& r)
{
    auto w = r.GetWidth();
    r.SetHeight(10);

    cout << "Expected area:\t " << (w * 10) <<
            "\nActual area:\t " << r.Area() << endl;
}

void LSP_TEST()
{
    Rectangle r(5, 5);
    Square s(5);
    process(s);
}
