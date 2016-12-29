#include <string>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;
#include <boost/any.hpp>
using namespace boost;

/*
 * ABSTRACT:
 * PersonListener provides an interface for us to create concrete observer objects that are invoked when a property has changed.
 * 
 * We make the Person class Observerable by storing a vector of these observers and allowing themto subscribe to the person.
 * When a modifiction of the person class is undertaken, it notifies the observers, letting them know what has changed.
 * 
 * The PersonChanged() method could do anything in it when the event is fired.
 * 
 * NOTE: If we had DEPENDENCY between properties, i.e. a can_vote property that is set when the age reaches 16.
 * The code for checking if the event should fire (notify) can get very complex. This is a difficulty with this method.
 */

class Person;
/*
 * This is the observer object, concrete versions of which are created that contain a method to invoke when the 
 * observed object, the person, has changed some property.
 */
class PersonListener
{
public:
    virtual ~PersonListener() = default;
    virtual void PersonChanged(const Person& person, const string& field, const any& value) = 0;
};

class ConsolePersonListener : public PersonListener
{
public:
    void PersonChanged(const Person& person, const string& field, const any& value) override
    {
        cout << "Person's " << field << " field has changed to value: ";
        if (field == "age")
            cout << any_cast<int>(value);
        cout << "\n";
    }
};

/*
 * This class is observable due to the fact it has a vector of listener objects that it will notify when something changes
 */
class Person
{
    int age;
    vector<PersonListener*> listeners;
public:

    explicit Person(const int age)
        : age{ age }
    {}

    int GetAge() const
    {
        return age;
    }

    void SetAge(const int age)
    {
        if (this->age == age)
            return;

        this->age = age;
        notify("age", this->age);
    }

    void notify(const string& field, const any& value)
    {
        for (const auto& l : listeners)
        {
            if(l)
            l->PersonChanged(*this, field, value);
        }
    }

    void subscribe(PersonListener* pl)
    {
        listeners.emplace_back(pl);
    }
};

void test_simple_observer()
{
    Person jordan{26};
    ConsolePersonListener cl;
    jordan.subscribe(&cl);

    jordan.SetAge(32);
}
