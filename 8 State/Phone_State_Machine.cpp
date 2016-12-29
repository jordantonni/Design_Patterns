#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

/*
 * ABSTRACT:
 * We have a map that maps a state to a vector of <Trigger, State> pairs.
 * 
 * For each state we add a rule to the vector, defining what trigger can be executed from that state and to what state it will result in.
 */

enum class State
{
    OffHook,
    Connecting,
    AnswerMachine,
    Connected,
    OnHook
};

inline ostream& operator<<(ostream& os, const State& state)
{
    switch (state)
    {
    case State::OffHook:
        os << "Off the hook";
        break;
    case State::Connecting:
        os << "Connecting";
        break;
    case State::Connected:
        os << "Connected";
        break;
    case State::AnswerMachine:
        os << "Answer Machine";
        break;
    case State::OnHook:
        os << "On hook";
        break;
    }
    return os;
}

enum class Triggers
{
    Pickup,
    Hangup,
    DialCall,
    Answered,
    LeaveMessage
};

inline ostream& operator<<(ostream& os, Triggers& triggers)
{
    switch (triggers)
    {
    case Triggers::Pickup:
        os << "Pick up the phone";
        break;
    case Triggers::Hangup:
        os << "Hangup the phone";
        break;
    case Triggers::DialCall:
        os << "Dial a call";
        break;
    case Triggers::Answered:
        os << "Answer";
    case Triggers::LeaveMessage:
        os << "Leave a message";
        break;
    }

    return os;
}

map<State, vector<pair<Triggers, State>>> rules;

void output_possible_actions(const State& state)
{
    cout << "Current State: [" << state << "] press the following: \n";

    size_t indx = 0;
    for (auto& t : rules[state])
    {
        cout << indx++ << " to " << t.first << "\t -> [" << t.second << "]" << endl;
    }
}

void select_action(const int indx, State& state)
{
    if (indx >= 0 && indx < rules[state].size())
    {
        state = rules[state].at(indx).second;
    }
}

void test_phone_state()
{
    rules[State::OnHook] = {
                { Triggers::Pickup, State::OffHook }
        };
    rules[State::OffHook] = {
                { Triggers::DialCall, State::Connecting }
        };
    rules[State::Connecting] = {
                { Triggers::Answered, State::Connected },
                { Triggers::LeaveMessage, State::AnswerMachine }
        };
    rules[State::Connected] = {
                { Triggers::Hangup, State::OnHook }
        };
    rules[State::AnswerMachine] = {
                { Triggers::Hangup, State::OnHook }
        };


    State currentState = State::OnHook;


    while (true)
    {
        output_possible_actions(currentState);
        int ind;
        cin >> ind;
        select_action(ind, currentState);
    }
}
