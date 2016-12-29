#include "Chat_Room.h"
#include "Chat_Person.h"
#include <algorithm>


Chat_Person* Chat_Room::PersonReference::operator->() const
{
    return &people[index];
}

void Chat_Room::broadcast(const string& sender, const string& message)
{
    for (auto& p : people)
    {
        if (p.name != sender)
            p.recieve(sender, message);
    }
}

Chat_Room::PersonReference Chat_Room::join(Chat_Person&& p)
{
    string join_msg = p.name + " joins the chat";
    broadcast("room", join_msg);

    p.room = this;
    people.emplace_back(p);
    return{people, people.size() - 1};
}

