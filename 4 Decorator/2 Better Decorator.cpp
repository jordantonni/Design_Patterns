#include <string>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

/*
 * ABSTRACT:
 * Logger3 can decorate any function by wrapping it in the operator() overload.
 *  - Function is passed in with templated return type R and argumenbts typename... Args
 *  - Sored in a function<R(Args...)> member variable
 *  - Have to partially specialise the Logger3 with <R(Args...)>, this partially specialised the class to let it know its using a function object
 *  
 *  make_logger helper templated function allows us to create a logger3 without having to specify the templated types when calling it
 *  due to how functions can infer templated params but constructors and classes cant (c++17 will fix this for constructors)
 */

template <typename>
struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args ...)>
{
    string func_name;
    function<R(Args ...)> func;

    Logger3(const function<R(Args ...)>& func, const string& name)
        : func{ func }
        , func_name { name }
    {}

    R operator()(Args ... args)
    {
        cout << "Decorating begin" << endl << endl;
        R res = func(args...);
        cout << endl << endl << "Decorating end" << endl;

        return res;
    }
};

double add(double a, double b)
{
    return a + b;
}

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args ...), const string& name)
{
    return Logger3<R(Args ...)> {
            function<R(Args ...)>(func),
            name
        };
}

void test_better_decorator()
{
    auto logged_add = make_logger3(add, "Adder");
    cout << logged_add(2, 5);

}
