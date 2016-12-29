#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * ABSTRACT:
 * Composite design pattern allows us to treat individual and collection of objects using the same interface.
 * Allows us to have macros (a sequence of commands)
 * 
 */

struct BankAccount2
{
    int amount;
    int overdraft_limit;

    BankAccount2(int am, int ov)
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

/*
 * This interface allows us to treat a single object or the composite class, CommandList, which derives from vector, the same.
 */
class ICommand
{
    virtual void execute() const = 0;
    virtual void undo() const = 0;
};

struct Command2 : ICommand
{
    BankAccount2& bank_account;
    int amount;

    enum class Action
    {
        Withdraw,
        Deposit
    } action;

    Command2(BankAccount2& ba, const int am, const Action act)
        : bank_account{ ba }
        , amount{ am }
        , action{ act }
    {}

    void execute() const override
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
    void undo() const override
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

/*
 * Composite pattern.
 * Note: Derive from vector of Commands and ICommand
 * Vector gives us an internal vector of Command objects
 * ICommand gives us the same interface to use
 * 
 * Implement each interface call by iterating though the individual objects and invoking the same function.
 * Initializer list lets us construct the composite object easily.
 */
class CommandList : vector<Command2>, ICommand
{
public:
    CommandList(const initializer_list<value_type>& IList)
        : vector<Command2>{ IList }
    {}

    void execute() const override
    {
        for(auto& o : *this)
            o.execute();
    }

    void undo() const override
    {
        for_each(rbegin(), rend(), [] (const Command2& cmd)
        {
            cmd.undo();
        });
    }
};


void test_composite_command()
{
    BankAccount2 ba { 100, -500 };
    CommandList commands
        {
            Command2 { ba, 1000, Command2::Action::Deposit },
            Command2 { ba, 300, Command2::Action::Withdraw },
            Command2 { ba, 1200, Command2::Action::Withdraw }
        };

    cout << "Initial Balance is: " << ba.amount << endl << endl;

    commands.execute();

    commands.undo();

    cout << endl << "After UNDO Balance is: " << ba.amount << endl << endl;
}
