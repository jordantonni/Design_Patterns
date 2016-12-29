#include <sstream>
#include <iostream>
#include <vector>

/*
 * Takes in an argument of any type, T.
 * Converts type T into a string
 * Returns the string
 * 
 * NOTE: This is the function we are using to actually convert the arg and put it in a string
 */
template <typename T>
std::string to_string_impl(const T& arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

/*
 * This is the base case for the recursion.
 * When all the agruments have been peeled off, the method below requires at least 1.
 * 
 * This method serves as the call of 0 args and ends the recursion.
 */
std::vector<std::string> to_string()
{
    return {};
}

/*
 * Takes in a list of arguments of types
 * typename... are the types, called Param
 * Param&... is the list of types, we now call that list params
 * 
 * We peel the first argument off ourselves, by specifying P1& p1 as a param
 * The remaining args are all bundled up in the Param&... list
 * 
 * NOTE: This function is really only resposible for peeling the first arg, sending it off to the above function, and then calling itself again
 * with the remaining args to recursively peel another arg off etc etc.
 */
template <typename P1, typename... Param>
std::vector<std::string> to_string(const P1& p1, const Param&... params)
{
    std::vector<std::string> vec;
    vec.emplace_back(to_string_impl(p1));

    const auto remainder = to_string(params...); // params... is expanded by the compiler to Param[1], Param[2] , Param[3] etc
    vec.insert(end(vec), begin(remainder), end(remainder));
    return vec;
}

void test_var_temp()
{
    const auto vec = to_string("hello", 1, 5.3, "World");

    for (const auto& x : vec)
    {
        std::cout << x << '\n';
    }
}
