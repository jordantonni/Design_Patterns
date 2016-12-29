#include <iostream>
#include <vector>
using namespace std;

/*
 * ABSTRACT:
 * Uses the same memento class idea as previous simple_memento, but stores each memento in a member vector of mementos.
 * 
 * As each operation that modifies the object is performed, a new memento snap shot is added to the vector.
 * 
 * Thus forming a history.
 * 
 * We can traverse back and forward though the history vector, setting the state of the object from one of the history memento objects.
 * This allows us to undo and redo.
 * 
 * NOTE: If there were a lot of fields to store for the state, we would probably serialize the memento objects and save them in a database.
 * Otherwise the size of the history vector could grow to be enourmous.
 */

class Memento
{
    int balance;
public:

    Memento(const int balance)
        : balance { balance }
    {}

    friend class BankAccount2;
};


class BankAccount2
{
    int balance;
    vector<Memento> history;
    size_t current;

public:

    explicit BankAccount2(const int balance)
        : balance { balance }, current { 0 }
    {
        history.emplace_back(Memento { balance });
    }

    void restore(const Memento& snap_shot)
    {
        balance = snap_shot.balance;
    }

    void undo()
    {
        if(current>0)
        {
            balance = history[--current].balance;
        }
    }

    void redo()
    {
        if(current < history.size()-1)
        {
            balance = history[++current].balance;
        }
    }

    const Memento& deposit(const int amount)
    {
        balance += amount;
        history.emplace_back(Memento { balance });
        return history[++current];
    }

    friend ostream& operator<<(ostream& oss, const BankAccount2& ba)
    {
        return oss <<
                "Balance: " << ba.balance << "\n";
    }
};


void test_memento()
{
    BankAccount2 ba { 55 };
    cout << ba << endl;
    auto s1 = ba.deposit(33);
    cout << ba << endl;
    auto s2 = ba.deposit(100);
    cout << ba << endl;

    ba.undo();
    ba.undo();
    ba.undo();
    ba.undo();
    cout << ba << endl;

    ba.redo();
    ba.redo();
    ba.redo();
    ba.redo();
    cout << ba << endl;



}
