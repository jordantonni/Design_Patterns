#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <memory>
#include <utility>
#include <sstream>
using namespace std;

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

/*
 * ABSTRACT:
 * Prototype pattern relies on having a correct deep copy implimentation available for the object you are prototyping.
 * In the case of c++ this means a correct copy constructor and copy assingment operator.
 * 
 * Depending on how the object to be prototyped is comprised, the object graph may be quite deep and thus require lots of 
 * memeber objects that follow pointers to other member objects. Increasing the complexity of the deep copy logic.
 * 
 * Serializing objects to some text or binary representation in a clone function allow us to fully copy an object
 * and then create new one by deserializing them.
 * 
 * This is can be easier and provide a more uniform API to the prototype pattern. As long as all classes in the object graph provide a 
 * serialization method, we have a uniform way to clone.
 * 
 * NOTE: This method allows us to have value types and pointer types as member variables using the same serialization code. No changes needed!
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

private:
    friend class boost::serialization::access;

    template <typename Ar>
    void serialize(Ar& ar, const unsigned int version)
    {
        ar & street;
        ar & city;
        ar & suite;
    }
};

struct ContactSer
{
    string name;
    Address work_address;

    friend std::ostream& operator<<(std::ostream& os, const ContactSer& obj)
    {
        return os
                << "name: " << obj.name
                << " work_address: " << obj.work_address;
    }

private:
    friend class boost::serialization::access;

    template <typename Ar>
    void serialize(Ar& ar, const unsigned int version)
    {
        ar & name;
        ar & work_address;
    }
};


void test_prototype_factory_serialization()
{
    ContactSer prototype { "Default", Address { "31 Privot Drive", "London", 999 } };

    string ser_data;

    auto clone = [&] (ContactSer c) mutable{
                ostringstream oss;
                boost::archive::text_oarchive oa(oss);
                oa << c;

                ser_data = oss.str();

                ContactSer result;
                istringstream iss(ser_data);
                boost::archive::text_iarchive ia(iss);
                ia >> result;

                return result;
            };

    ContactSer me = clone(prototype);
    me.name = "Jay";
    me.work_address.suite = 101;

    cout << ser_data << endl;
}
