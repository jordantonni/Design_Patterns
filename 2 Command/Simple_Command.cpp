#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * ABSTRACT:
 * Instead of just calling the deposit and withdraw methods of the BankAccount
 * We create a command object that has a reference to the object we are interested in, the BankAccount + an enum of what action to take and the argument to forward.
 * 
 * This allows us to create commands on invoke on the BankAccount and store them in a data structure to invoke when we want or all at once etc.
 * 
 * NOTE: If we instead stored a unique ID for the BankAccount object in the Command class instead of a reference, we could easily serailize the commands
 * to file etc to provide an audit trail.
 * (Cant really serilize references or pointers as their memory location will change)
 * 
 * UNDO / REDO functionality:
 *  Can go through the vector of commands in reverse order and invoke a function that does the oppostive of what was called, this would undo all commands.
 *  Redo is easy as you just go though the commands again.
 */

struct BankAccount
{
    int amount;
    int overdraft_limit;

    BankAccount(int am, int ov)
        : amount{ am }
        , overdraft_limit{ ov }
    {}

    void deposit(int arg_amount)
    {
        amount += arg_amount;
        cout << "Deposited: " << arg_amount << ", Balance is now: " << amount << "\n";
    }

    void withdraw(int arg_amount)
    {
        if (amount - arg_amount >= overdraft_limit)
            amount -= arg_amount;

        cout << "Withdrew: " << arg_amount << ", Balance is now: " << amount << "\n";
    }
};

struct Command
{
    BankAccount& bank_account;
    int amount;

    enum class Action
    {
        Withdraw,
        Deposit
    } action;

    Command(BankAccount& ba, const int am, const Action act)
        : bank_account{ ba }
        , amount{ am }
        , action{ act }
    {}


    void execute() const
    {
        switch (action)
        {
        case Action::Deposit:
            bank_account.deposit(amount);
            break;
        case Action::Withdraw:
            bank_account.withdraw(amount);
            break;
        default:
            break;
        }
    }

    /*
     * By swapping the withdraw and deposit here we basically get a naive implementation of an UNDO
     */
    void undo() const
    {
        switch (action)
        {
        case Action::Withdraw:
            bank_account.deposit(amount);
            break;
        case Action::Deposit:
            bank_account.withdraw(amount);
            break;
        default:
            break;
        }
    }
};


void test_command()
{
    BankAccount ba { 100, -500 };
    vector<Command> commands
        {
            Command { ba, 1000, Command::Action::Deposit },
            Command { ba, 300, Command::Action::Withdraw },
            Command { ba, 1200, Command::Action::Withdraw }
        };

    cout << "Initial Balance is: " << ba.amount << endl << endl;

    for (auto& o : commands)
        o.execute();

    for_each(rbegin(commands), rend(commands), [] (Command& cmd)
    {
        cmd.undo();
    });

    cout << endl << "After UNDO Balance is: " << ba.amount << endl << endl;
}
