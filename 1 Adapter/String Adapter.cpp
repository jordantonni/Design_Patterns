#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/algorithm/string.hpp>
using namespace std;

/*
 * ABSTRACT:
 * Want to convert a string to lowercase and split on the spaces.
 * The functions to do this arent easily discovered due to being a global function that works on a string from the algorithim header.
 * 
 * By wrapping the string in our own adapter class, we have more control over how the methods work and can provide an easier to use API.
 */


class string_adapter
{
    string inner_string;

public:
    string_adapter(const string& s)
        : inner_string{ s }
    {}

    string_adapter to_lower() const
    {
        string result { inner_string };
        transform(begin(result), end(result), begin(result), ::tolower);
        return result;
    }

    vector<string> split(const string& delimiter = " ") const
    {
        vector<string> result_tokens;
        boost::split(result_tokens, inner_string, boost::is_any_of(delimiter), boost::token_compress_on);
        return result_tokens;
    }
};


void test_string_adapter()
{
    /* Without Adapter:
     *      BAD: Have to know about the global functions split, ::tolower, is_any_of
     */
    string s { "hello    there" };
    transform(begin(s), end(s), begin(s), ::tolower);
    vector<string> tokens;
    boost::split(tokens, s, boost::is_any_of(" "));

    for (const auto& x : tokens)
        cout << "<" << x << ">" << endl;

    cout << endl;

    /*
     * With Adapter:
     *      GOOD: We have an easy to use interface with full control over how each method is implemented.
     */
    string_adapter sa { "hello    there buddy" };
    auto tokens_2 = sa.to_lower().split();
    for (const auto& x : tokens_2)
        cout << "<" << x << ">" << endl;

}
