#include <iostream>
using namespace std;

/*
 * ABSTRACT:
 * Memento class is really a POD (Plain Old Data Structure) / Token class, that only stores data.
 * 
 * Each time the BankAccount object modifies it's fields, a Memento is created storing a snap shot of the current state.
 * 
 * A restore method takes a memento snapshot and uses it to revert all its own fields to the snapshots state.
 */

class Simple_Memento
{
    int balance;
public:

    Simple_Memento(const int balance)
        : balance { balance }
    {}

    friend class BankAccount;
};


class BankAccount
{
    int balance;
public:

    explicit BankAccount(const int balance)
        : balance { balance }
    { }

    void restore(const Simple_Memento& snap_shot)
    {
        balance = snap_shot.balance;
    }

    Simple_Memento deposit(const int amount)
    {
        balance += amount;
        return { balance };
    }

    friend ostream& operator<<(ostream& oss, const BankAccount& ba)
    {
        return oss <<
                "Balance: " << ba.balance << "\n";
    }
};


void test_simple_memento()
{
    BankAccount ba { 100 };
    cout << ba << endl;
    auto s1 = ba.deposit(320);
    cout << ba << endl;
    auto s2 = ba.deposit(320);
    cout << ba << endl;

    ba.restore(s1);
    cout << ba << endl;
}
