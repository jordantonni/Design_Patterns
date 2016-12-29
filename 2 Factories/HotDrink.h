#pragma once
#include <iostream>

using std::cout;
using std::endl;


/*
 * Allows us to create factories that create any HotDrink
 */
struct HotDrink
{
    virtual void Prepare(int volume) = 0;
};

struct Tea : HotDrink
{
   void Prepare(int volume) override
   {
       cout << "Take tea bag, boil water, pour " << volume << "ml" << endl;
   }
};

struct Coffee : HotDrink
{
   void Prepare(int volume) override
   {
       cout << "Grind coffee beans, boil water, pour " << volume << "ml" << endl;
   }
};