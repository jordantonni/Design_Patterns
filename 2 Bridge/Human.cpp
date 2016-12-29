#include "Human.h"
#include <iostream>

void HumanImpl::greet()
{
    std::cout << "Hello" << std::endl;
}

Human::Human()
    : impl { new HumanImpl }
{}

Human::~Human()
{
    delete impl;
}

void Human::greet() const
{
    impl->greet();
}

