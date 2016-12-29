#pragma once
#include "PersonBuilder.h"
using namespace std;

/*
 * Accesses the person via inherited reference.
 * Fluent interface to set each member variable of person.
 */
class PersonJobBuilder : public PersonBuilder
{
    typedef PersonJobBuilder Self;

public:

    explicit PersonJobBuilder(Person& person)
        : PersonBuilder(person)
    {}

    //Fluent interface to set person employment members
    //Note the return of this object ref allowing method chaining
    //Also note the fluent naming verbage
    Self& at(string company_name)
    {
        person.company_name = company_name;
        return *this;
    }

    Self& as_a(string position)
    {
        person.position = position;
        return *this;
    }

    Self& earning(int annual_income)
    {
        person.annual_income = annual_income;
        return *this;
    }
};
