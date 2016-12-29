#include <iostream>
#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"
using namespace std;

/*
 * ABSTRACT:
 * Create is a static member function of person that returns a person builder.
 * The person builder creates a person object and exposes two other builders that inherit from it.
 * One for the address and the other for the employment. 
 * 
 * Each of these two builders inherit the access to the person, made in person builder.
 * They expose a fluent interface, allowing us to set each of the person members that pertain to their builder.
 */
void FacetTest()
{
    Person p = Person::create()
        .lives().at("26 Craiganboy Park").with_postcode("BT40 3DN").in("Larne")
        .works().at("Google").as_a("Software Developer").earning(128000);

    cout << p << endl;
}