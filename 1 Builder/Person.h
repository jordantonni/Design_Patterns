#pragma once
#include <string>
#include <ostream>
using namespace std;

class PersonBuilder;

class Person
{
    //address
    string street_address;
    string post_code;
    string city;

    //employment
    string company_name;
    string position;
    int annual_income = 0;

    //Private, as only the person builder creates a person.
    Person() {}
public:

    Person(Person&& other) noexcept
        : street_address(std::move(other.street_address))
        , post_code(std::move(other.post_code))
        , city(std::move(other.city))
        , company_name(std::move(other.company_name))
        , position(std::move(other.position))
        , annual_income(other.annual_income)
    {}

    Person& operator=(Person&& other) noexcept
    {
        if (this == &other)
            return *this;
        street_address = std::move(other.street_address);
        post_code = std::move(other.post_code);
        city = std::move(other.city);
        company_name = std::move(other.company_name);
        position = std::move(other.position);
        annual_income = other.annual_income;
        return *this;
    }


    friend std::ostream& operator<<(std::ostream& os, const Person& obj)
    {
        return os
                << "street_address: " << obj.street_address
                << " post_code: " << obj.post_code
                << " city: " << obj.city
                << " company_name: " << obj.company_name
                << " position: " << obj.position
                << " annual_income: " << obj.annual_income;
    }
    
    //public create exposes the only way to make a person.
    static PersonBuilder create();

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};
