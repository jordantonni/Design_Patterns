#pragma once
#include "PersonBuilder.h"
using namespace std;

/*
 * Accesses the person via inherited reference.
 * Fluent interface to set each member variable of person.
 */
class PersonAddressBuilder : public PersonBuilder
{
    typedef PersonAddressBuilder Self;

public:

    explicit PersonAddressBuilder(Person& person)
        : PersonBuilder(person)
    {}

    //Fluent interface to set person address memebers
    //Note the return of this object ref allowing method chaining
    //Also note the fluent naming verbage
    Self& at(string street_address)
    {
        person.street_address = street_address;
        return *this;
    }

    Self& with_postcode(string post_code)
    {
        person.post_code = post_code;
        return *this;
    }

    Self& in(string city)
    {
        person.city = city;
        return *this;
    }
};
