#include <iostream>
#include <boost/bimap.hpp>
#include <ostream>
using namespace std;
using namespace boost;

/*
 * ABSTRACT:
 * Users can have the same names. 
 * We store the names in a static bi-directional map of the user class.
 * 
 * When we add a new name it gets added to the map with the id of the object.
 * Check if the name already exists in the constructor of each user object.
 * 
 * The flyweight in this example is the key value that is used to find names in the list.
 */

struct User
{
    User(const string& first_name, const string& last_name)
        : first_name{ add(first_name) }
        , last_name{ add(last_name) }
    {}


    const string& get_first_name() const
    {
        return names.left.find(first_name)->second;
    }

    const string& get_last_name() const
    {
        return names.left.find(last_name)->second;
    }


    friend std::ostream& operator<<(std::ostream& os, const User& obj)
    {
        return os
            << "first_name: " << obj.get_first_name() << " at index " << obj.first_name
            << " last_name: " << obj.get_last_name() << " at index " << obj.last_name;
    }

protected:
    static bimap<int, string> names;
    static int user_seed;;

    int first_name;
    int last_name;

    static int add(const string& name)
    {
        auto names_iterator = names.right.find(name);
        if (names_iterator == names.right.end())
        {
            int id = ++user_seed;
            names.insert(bimap<int, string>::value_type(id, name));
            return id;
        }

        return names_iterator->second;
    }
};

bimap<int, string> User::names {};
int User::user_seed = 0;

void test_flyweight()
{
    User person1 { "Jordan", "Tonni" };
    User person2 { "Ryan", "Tonni" };

    cout << person1 << endl << person2 << endl;
}
