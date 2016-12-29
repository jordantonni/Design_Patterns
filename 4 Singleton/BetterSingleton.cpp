#include <string>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

/*
 * ABSTRACT:
 * Private constructor.
 * Delete copy assingment operator.
 * Delete copy constructor.
 * Static method to return static function variable of the object.
 * 
 * This is the canonocial way to implement this singleton pattern in c++.
 */

class SingletonDatabase
{
    map<string, int> capitals;

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

    /*
     * NOTE: C++ allows us to create static function variables. These are only created once for all function invocations.
     * Returning a reference to this single static object is the best way to implement the singleton pattern.
     */
    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    void print_city_population()
    {
        for(auto& x : capitals)
            cout << x.first << " has population: " << x.second << endl;
    }
};


void test_better_singletion()
{
    auto& sd = SingletonDatabase::get();
    sd.print_city_population();

}