#pragma once
#include <map>
#include <string>
#include <memory>
#include "TeaFactory.h"
#include "CoffeeFactory.h"

using namespace std;

/*
 * Directs the creation of drinks by delegating what drink factory to call for a specific string.
 * 
 * Uses a hashmap to map between strings and their respective drink factory.
 */

class DrinkFactory
{
    map<string, unique_ptr<HotDrinkFactory>> factories;

public:
    DrinkFactory()
    {
        factories["tea"] = make_unique<TeaFactory>();
        factories["coffee"] = make_unique<CoffeeFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& drink_type, int volume)
    {
        auto drink = factories[drink_type]->make();
        drink->Prepare(volume);
        return drink;
    }
};
