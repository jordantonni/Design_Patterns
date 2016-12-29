#include <iostream>
#include <memory>
#include <boost/lexical_cast.hpp> 
using namespace boost;
using namespace std;

/*
 * ABSTRACT:
 * Our BankAccount below depends on instantiating and passing in a logger object.
 * 
 * But if we dont have a logger or don't want one for this specific case, then we need a Null Object.
 */

struct ILogger
{
    virtual ~ILogger() = default;
    virtual void info(const string& s) = 0;
    virtual void warn(const string& s) = 0;
};

/*
 * Null object just acts to serve the dependency. Provides no functionality.
 * 
 * Note: Derives from the base of the class we are providing a null object of
 */
struct NullLogger : ILogger
{
    ~NullLogger() override
    {}

    void info(const string& s) override
    {}

    void warn(const string& s) override
    {}
};

struct BankAccout
{
    std::shared_ptr<ILogger> log;
    string name;
    int balance = 0;

    BankAccout(const std::shared_ptr<ILogger>& logger, const string& name, int balance)
        : log{ logger }
        , name{ name }
        , balance{ balance }
    {}

    void deposit(int amount)
    {
        balance += amount;

        ostringstream os;
        os << "Deposited $" << amount << " into account";
        log->info(os.str());
    }

    void withdraw(int amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            ostringstream os;
            os << "Withdrew $" << amount << " from account";
            log->info(os.str());
        }
        ostringstream os;
        os << "Insuffiecient funds to withdraw $" << amount << " from account";
        log->warn(os.str());
    }
};

int main()
{
    auto nl = std::make_shared<NullLogger>();
    BankAccout ba { nl, "Account1", 7500000 };

    return 0;
}
