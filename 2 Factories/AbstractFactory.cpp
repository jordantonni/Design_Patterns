#include "CoffeeFactory.h"
#include <string>
#include <iostream>
#include "TeaFactory.h"
#include "DrinkFactory.h"

using namespace std;

/*
 * ABSTRACT:
 * Creating a base HotDrink class allows our HotDrink factories to work with any HotDrink class that inheriates from HotDrink.
 * The Base HotDrinkFactory interface allows us to create different factories specific for each drink.
 * 
 * The drink factory then maps a string to a HotDrinkFactory pointer, which is instantiated with a concrete factory for that specific drink string.
 */

void test_AbstractFactory()
{
    DrinkFactory DF;
    auto drink =  DF.make_drink("coffee", 200);
    auto drink2 = DF.make_drink("tea", 300);

}