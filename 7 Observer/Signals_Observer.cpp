#include <string>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;
#include <boost/any.hpp>
#include <boost/signals2.hpp>
using namespace boost;

/*
 * ABSTRACT:
 * The Boost/Signals2 library provides an easy way to use the observer pattern.
 * We define an observer interface that holds the signal bus.
 * 
 * When we call a method on the person class we notify the signal.
 * 
 * We connect to a "slot" on the signal that specifies a function to execute when signaled.
 */


template <typename T>
struct INotifyPropertyChanged
{
    virtual ~INotifyPropertyChanged() = default;
    signals2::signal<void(T&, const string&)> PropertyChanged;
};

class Person3 : public INotifyPropertyChanged<Person3>
{
    int age;
public:

    explicit Person3(int age)
        : age{ age }
    {}

    int GetAge() const
    {
        return age;
    }

    void SetAge(const int age)
    {
        if (age == this->age) return;

        this->age = age;
        PropertyChanged(*this, "age");
    }
};


void test_boost_signals_observer()
{
    Person3 jordan { 26 };
    jordan.PropertyChanged.connect([] (Person3& person, const string& property_name)
    {
        cout << property_name << " has been changed" << "\n";
    });

    jordan.SetAge(27);
}
