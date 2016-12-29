#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <memory>
#include <utility>
using namespace std;

/*
 * ABSTRACT:
 * Prototype Factory encapsulates the protoytype objects into a class of their own, the factory.
 * 
 * It provides static factory methods to create versions of objects from different prototypes.
 * 
 * This allows us to have a place to keep each of the prototypes we create without having them as global objects
 * just hanging around. The point of them is never to be used, only to be passed in to the copy construtor 
 * of specific objects we wish to create!
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
        , work_address{ work_address }
    { }

    /*
     * This deep copy, copy constructor is pivitol to the prototype pattern.
     * It allows us to take in a prototype object and set the fields of our new object using its partially instantiated data.
     * 
     * Without modifying the protoype itself.
     */
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

/*
 * Two different static prototypes with different addresses.
 * 
 * A private function used to create a new contact with the specific details we want + one of the prototypes use to instantate some of the data.
 * 
 * Public functions expose different types of objects we can make. Typically we would have one for each of the static prototypes we store.
 */
class EmployeeFactory
{
private:
    static unique_ptr<Contact> new_employee(const string& name, const int suite, const Contact& proto)
    {
        auto result = make_unique<Contact>(proto);
        result->name = name;
        result->work_address->suite = suite;

        return result;
    }

public:
    static Contact main_office_employee_prototype;
    static Contact aux_office_employee_prototype;

    static unique_ptr<Contact> make_main_office_employee(const string& name, int suite)
    {
        return new_employee(name, suite, main_office_employee_prototype);
    }

    static unique_ptr<Contact> make_aux_office_employee(const string& name, int suite)
    {
        return new_employee(name, suite, aux_office_employee_prototype);
    }
};

/*
 * Due to the one declaration rule
 * We have to declare our static member variables in a source file. If it was in the header they would be declared multiple times
 * Once for each include.
 * 
 * Even though we arent in a head here, it still forces us to do this outside of the class scope.
 */
Contact EmployeeFactory::main_office_employee_prototype { "", new Address{ "EDC 1 Sandyford Industrial Estate", "Dublin", 0 } };
Contact EmployeeFactory::aux_office_employee_prototype { "", new Address{ "EDB 2 Sandyford Industrial Estate", "Dublin", 0 } };

void test_prototype_factory()
{
    auto john = EmployeeFactory::make_main_office_employee("John", 101);
    auto jayne = EmployeeFactory::make_aux_office_employee("Jayne", 111);
    cout << *jayne << endl << *john << endl << endl;
}
