#include <iostream>
#include <functional>
#include <string>
using namespace std;

/*
 * ABSTRACT:
 * Wrap some function with extra logic that achieves something.
 * Typically before and after the function itself.
 * 
 * E.G. A logger than logs information before and after calling the function.
 */


// Naive Approach 1 
// Restricts the type of function you can pass in due to specifying the signiture of func.
struct ILogger
{
    string name;
    function<void()> func;

    ILogger(const string& name, const function<void()>& func)
        : name{ name }
        , func{ func }
    {}

    // Wrap the invocation of the function with our logging logic
    void operator()()
    {
        cout << "LOGGING: Entering func " << name << endl;
        func();
        cout << "LOGGING: Exiting func " << name << endl;
    }
};

// More generic approach
template <typename Func>
struct Logger2
{
    Func func;
    string name;

    Logger2(Func func, const string& name)
        : func{ func }
        , name{ name }
    {}

    // Wrap the invocation of the function with our logging logic
    void operator()()
    {
        cout << "LOGGING: Entering func " << name << endl << endl;;
        func();
        cout << endl << "LOGGING: Exiting func " << name << endl;
    }
};

// Constructor of Logger2 cannot infer the type of the lambda.
// Templated functions can infer type of their arguments.
template <typename Func>
auto make_logger2(Func func, const string& name)
{
    return Logger2<Func> { func, name };
}


void test_function_decorator()
{
    auto logger = make_logger2([]()
                               {
                                   cout << "hello there " << endl;
                               }, "[Templated Function]");
    logger();
}
