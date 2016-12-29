#pragma once
#include <string>

/*
 * Typical Pimpl implementation.
 * The HumanImpl class is what contains the logic for doing stuff.
 * 
 * The Human class has a memeber pointer to the implementation.
 * The Human class only exposes it's API
 * Each API calls the Impl class to carry out the actually implementation of that API.
 * 
 */
struct HumanImpl
{
    void greet();
};

struct Human
{
private:
    // This implementation of human is carried out in the HumanImpl class
    HumanImpl* impl;

public:
    Human();
    ~Human();

    void greet() const;
};
