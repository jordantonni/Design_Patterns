#pragma once
#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

/*
 * Creates the initial person object and provides access to the specific builders.
 * Also allows specific builders access to the person created though inheritance of the Person reference.
 */
class PersonBuilder
{
    Person p;

protected:
    Person& person;

    explicit PersonBuilder(Person& person)
        : person{ person }
    {}

public:
    PersonBuilder()
        : person{ p }
    {}

    operator Person()
    {
        return move(person);
    }

    PersonAddressBuilder lives();
    PersonJobBuilder works();
};


