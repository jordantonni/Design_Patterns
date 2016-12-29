#include "Chat_Person.h"
#include "Chat_Room.h"


Chat_Person::Chat_Person(const string& name)
    : name{ name }
{}

void Chat_Person::say(const string& message) const
{
    room->broadcast(name, message);
}

void Chat_Person::recieve(const string& origin, const string& message) const
{
    string s{origin + ": \"" + message + "\""};
    cout << "[" << name << "'s chat session] " << s << "\n";
}



