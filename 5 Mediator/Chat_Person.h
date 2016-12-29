#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Chat_Room;

struct Chat_Person
{
    string name;
    Chat_Room* room = nullptr;

    explicit Chat_Person(const string& name);

    void say(const string& message) const;

    void recieve(const string& origin, const string& message) const;
};

