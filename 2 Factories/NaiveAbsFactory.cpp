#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include "HotDrink.h"

using namespace std;

/*
 * ABSTRACT:
 * Creating objects that belong to some hierarchy.
 * We want to be able to choose what subtype to create by passing in some value.
 * 
 * Naive method, make_drink, will become too large and complex when more types are added.
 */

unique_ptr<HotDrink> make_drink(string drink)
{
    transform(begin(drink), end(drink), begin(drink), ::tolower);
    unique_ptr<HotDrink> result;

    if (!drink.compare("tea")){
        result = make_unique<Tea>();
        result->Prepare(200);
    }
    else if (!drink.compare("coffee")){
        result = make_unique<Coffee>();
        result->Prepare(200);
    }
    return result;
}

void test_NaiveAbsFactory()
{
    auto d = make_drink("tea");
}
