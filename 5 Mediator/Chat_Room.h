#pragma once
#include<string>
#include<vector>
using std::vector;
using std::string;

/*
 * ABSTRACT:
 * The Chat Room serves as the mediator. All communication between People happens though this class.
 * 
 * People are created and put into a Chat Rooms vector list of people. Which returns a reference to the person in that vector.
 * From this returned person reference, we call methods on the person, such as say().
 * 
 * This in turn invokes the communication methods on the Chat Room, broadcasting the message to all people in the vector of people the chat room contains.
 * 
 * Broadcast invokes the recieve method for each person it has, which in turn prints the message out
 */

struct Chat_Person;


struct Chat_Room
{
    vector<Chat_Person> people;

    class PersonReference
    {
        vector<Chat_Person>& people;
        size_t index;
    public:

        PersonReference(vector<Chat_Person>& persons, const unsigned index)
            : people(persons)
            , index(index)
        {}

        Chat_Person* operator->() const;
    };

    void broadcast(const string& sender, const string& message);
    PersonReference join(Chat_Person&& p);
};
