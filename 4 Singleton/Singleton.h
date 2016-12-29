#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>

using std::string;
using std::map;
using std::cout;
using std::endl;
using std::fstream;

class SingletonDatabase
{
    std::map<string, int> capitals;

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
        ++count;
    }


public:
    static int count;
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
