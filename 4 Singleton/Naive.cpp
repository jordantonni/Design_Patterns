#include <string>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

/*
 * ABSTRACT:
 * We want to ensure only one instance of the SingletonDatabase: 
 * The class it not static, but we hide the constructor as private and delcar the copy constructor/assingment operator as deleted.
 * 
 * Private Static pointer to an instance of itself is instantiated in a factory method of the class.
 * This can ensure only one instance of the class is created. And passed back to the caller.
 * 
 * All interaction with the class is achieved through this pointer.
 * 
 * PROBLEMS: There is no real way to delete and free the memory of the object stored in the instance pointer.
 * No such thing as a satic dectructor.
 */

class SingletonDatabase
{
    map<string, int> capitals;
    static SingletonDatabase* instance;

    SingletonDatabase()
    {
        cout << "Initializing Database" << endl;

        fstream file("FakeData.txt");
        string city, str_population;

        while (getline(file, city)){
            getline(file, str_population);
            int population = stoi(str_population);

            capitals[city] = population;
        }
        file.close();
    }


public:
    // Ensures the singleton can't be copied
    SingletonDatabase(const SingletonDatabase& rhs) = delete;
    SingletonDatabase& operator=(const SingletonDatabase& rhs) = delete;


    // Only way we provide to get the object. Note it check if it is already made. Ensuring only one.
    // NOTE: Note thread safe. Race condition on the if statement could result it multiple new SingletonDatabases.
    static SingletonDatabase* get_instance()
    {
        if (!instance)
            instance = new SingletonDatabase;
        return instance;
    }

    void print_city_population()
    {
        for(auto& x : capitals)
            cout << x.first << " has population: " << x.second << endl;
    }
};

SingletonDatabase* SingletonDatabase::instance = nullptr;

void test_naive()
{
    auto sd = SingletonDatabase::get_instance();
    sd->print_city_population();

}
