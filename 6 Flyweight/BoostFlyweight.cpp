#include <iostream>
#include <boost/bimap.hpp>
#include <ostream>
#include <boost/flyweight.hpp>
using namespace std;
using namespace boost;

/*
 * ABSTRACT:
 * Boost flyweight just wraps the data types that you wish to flyweight.
 * 
 * Very easy
 * 
 * Here the flyweight objects are the first and last names.
 */
struct User2
{
    flyweight<string> first_name;
    flyweight<string> last_name;

    User2(const string& first_name, const string& last_name)
        : first_name{ first_name }
        , last_name{ last_name }
    {}

    friend std::ostream& operator<<(std::ostream& os, const User2& obj)
    {
        return os
                << "first_name: " << obj.first_name
                << " last_name: " << obj.last_name;
    }
};

void test_boost_flyweight()
{
    User2 Jordan { "Jord", "Tonni" };
    User2 Ryan { "Ryan", "Tonni" };

    cout << boolalpha <<
            (&Jordan.last_name.get() == &Ryan.last_name.get()) <<
            endl;


    cout << Jordan << '\n' << Ryan << endl;
}
