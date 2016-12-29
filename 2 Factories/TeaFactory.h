#pragma once
#include "HotDrinkFactory.h"

/*
 * Creates a tea object
 */

struct TeaFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() override
    {
        return std::make_unique<Tea>();
    }
};