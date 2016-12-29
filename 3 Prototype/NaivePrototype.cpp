#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
using namespace std;

/*
 * ABSTRACT:
 * The idea with the prototype pattern here is that we want to create a partially instantiated Contact with some address.
 * Then pass this contact into another one (via a copy constructor) which is the deep copy part.
 * 
 * This then allows use to fill in the extra details of the new Contacts we make, without having to keep specifying the information
 * that the prototyope contact will fill out for us.
 * 
 * Note how the deep copying provided by the copy constructor we make allows us to change each new contacts address without altering the "base" prototype.
 */

struct Address
{
    string street;
    string city;
    int suite;

    friend std::ostream& operator<<(std::ostream& os, const Address& obj)
    {
        return os
                << "street: " << obj.street
                << " city: " << obj.city
                << " suite: " << obj.suite;
    }
};

struct Contact
{
    string name;
    Address* work_address;

    Contact(const string& name, Address* const work_address)
        : name{ name }
        , work_address { new Address{ *work_address } }
    { }

    Contact(const Contact& rhs)
        : name{ rhs.name }
        , work_address { new Address{ *rhs.work_address } }
    { }

    ~Contact() noexcept
    {
        delete work_address;
    }

    friend std::ostream& operator<<(std::ostream& os, const Contact& obj)
    {
        return os
                << "name: " << obj.name
                << " work_address: " << *obj.work_address;
    }
};

void test_naive_prototype()
{
    /*
     * We use this prototype contact to instantiate some of the member data that will be the same 
     * for other contacts.
     * 
     * NOTE: Memory leak with the new Address being created for the prototype. 
     *       The constructor will new up and new one of these also.
     */
    Contact prototype_contact { "", new Address{ "123 Privot Lane", "London", 0 } };

    Contact john { prototype_contact };
    john.name = "John";
    john.work_address->suite = 100;

    Contact jayne { prototype_contact };
    jayne.name = "Jayne";
    jayne.work_address->suite = 101;

    cout << jayne << endl << john << endl;
}
