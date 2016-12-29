#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <mutex>
#include <algorithm>
using namespace std;
#include <boost/any.hpp>
using namespace boost;

/*
 * ABSTRACT:
 * Two Problems:
 *  1) Vector of listeners is not thread safe. We need to ensure only 1 instance of the observer is added to the vector of listeners, else we will get multiple notifications
 *  2) Reentrancy: Reentrant function can be interupted halfway through its execution and called again with no bad side efeccts.
 *
 *  - We fix the problem of subscribing the same listener to the vector collection by checking it doesnt already exist.
 *  - We also fix the problem of having the notify / subscribe / unsubscribe methods all interact with vector of listeneds in an unsafe way
 *    by creating a static mutex and wrapping it in a lock_guard at the start of each method.
 *    
 *  PROBLEM: 
 *      The notify() function locks the mutex, then calls the listeners PersonChanged() method. If it in turn tries to invoke a method on the person
 *      that will lock the mutex, we get a deadlock. This is a REENTRANCY problem.
 */


class Person2;

class PersonListener2
{
public:
    virtual ~PersonListener2() = default;
    virtual void PersonChanged(const Person2& person, const string& field, const any& value) = 0;
};

class ConsolePersonListener2 : public PersonListener2
{
public:
    void PersonChanged(const Person2& person, const string& field, const any& value) override
    {
        cout << "Person's " << field << " field has changed to value: ";
        if (field == "age")
            cout << any_cast<int>(value);
        cout << "\n";
    }
};

static mutex mtx;

class Person2
{
    int age;
    vector<PersonListener2*> listeners;
public:

    explicit Person2(const int age)
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
        lock_guard<mutex> guard { mtx };

        for (const auto& l : listeners)
        {
            if (l)
                l->PersonChanged(*this, field, value);
        }

        // Erase remove idiom. Remove puts all elements that match criteria at the end of vector, returning iterator to start of that area
        // Erase uses this as the start position to actually remove them.
        listeners.erase(
                        remove(begin(listeners), end(listeners), nullptr), end(listeners));
    }

    void subscribe(PersonListener2* pl)
    {
        lock_guard<mutex> guard { mtx };

        if (std::find(begin(listeners), end(listeners), pl) == end(listeners))
            listeners.emplace_back(pl);
    }

    void unsubscribe(PersonListener2* pl)
    {
        lock_guard<mutex> guard { mtx };

        auto l = find(begin(listeners), end(listeners), pl);
        if (l != end(listeners))
            *l = nullptr;
    }
};

void test_thread_safe_observer()
{
    Person2 jordan { 26 };
    ConsolePersonListener2 cl;
    jordan.subscribe(&cl);

    jordan.SetAge(32);
    jordan.SetAge(27);

    jordan.unsubscribe(&cl);
    jordan.SetAge(43);
    jordan.SetAge(31);
}
