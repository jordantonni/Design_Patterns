#include "stdafx.h"
#pragma once

using namespace std;

struct Journal
{
    string title;
    vector<string> entries;

    explicit Journal(string&& title)
        : title(title) {}

    void add(const string& entry)
    {
        entries.emplace_back(entry);
    }

    /*
     * Save method isnt really part of this classes responsibility.
     * This class is only for the Journal itself. Shouldnt also have the 
     * responsibilty of saving the object.
     */
    void save(const string&& filepath)
    {
        ofstream file(filepath);
        size_t entry_count = 0;

        for (auto& entry : entries){
            file << entry << endl;
            ++entry_count;
        }
        cout << "Saved " << entry_count << " entries to " << filepath << endl;
    }
};

// --------------------------------------------------------------------------------------------//

//SRP

/*
 * Here we create another class that will be responsible 
 * only for saving a Journal.
 */
struct PersistenceManager
{
    static void save(const Journal& journal, const string& filepath)
    {
        ofstream file(filepath);
        size_t entry_count = 0;

        for (auto& entry : journal.entries){
            file << entry << endl;
            ++entry_count;
        }
        cout << "Saved " << entry_count << " entries to " << filepath << endl;
    }
};

void SRP_TEST()
{
    Journal journal("MyJournal");
    journal.add("Dear diary, this is my first entry");

    //journal.save("Myjournal.txt");
    PersistenceManager::save(journal, "MyJournal.txt");
}
