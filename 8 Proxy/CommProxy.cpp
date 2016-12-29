#include <iostream>
#include <string>
using namespace std;

/*
 * ABSTRACT:
 * Pong object realises the Pingable interface.
 * 
 * HTTP_REST_Pong can also realise the Pingable interface, even though the object itself is a rest service on another machine somewhere.
 * It is a proxy class that achieves the same functionality but in another different way. 
 * 
 * NOTE: How we could use the HTTP_REST_Pong instead of the Pong class without any code changes to the code using them.
 */

struct Pingable
{
    virtual ~Pingable() = default;
    virtual wstring ping(const wstring& msg) = 0;
};

struct Pong : Pingable
{
    wstring ping(const wstring& msg)
    {
        return msg + L" pong";
    }
};

// Proxy class
struct HTTP_REST_Pong : Pingable
{
    /*
     * This class can then proxy a message into a pingable object that is located
     * on another web server etc.
     * 
     * As it implements the same interface, the functionality is reserved but how it achieves it is different.
     */
    
    wstring ping(const wstring& msg) override;
};

void try_pong(Pong& p)
{
    wcout << p.ping(L"Ping") << "\t";
}

void test_comm_proxy()
{
    Pong pp;
    for (int i = 0; i < 10; ++i)
    {
        try_pong(pp);
    }
    
}