#pragma once
#include "HotDrink.h"
#include <memory>

/*
 * Abstract Factory Interface that all hot drink factories must implement
 * 
 * Allows us to hold a pointer to any specific hot drink factory by using this type as the polymorphic base.
 * 
 * NOTE: This doesnt have to be pure virtual. If all the specific factories that derive from this HotDrinkFactory
 *       require something similar to be done in order to make a concrete object, it can be done in this class.
 */

struct HotDrinkFactory
{
    virtual std::unique_ptr<HotDrink> make() = 0;
};
