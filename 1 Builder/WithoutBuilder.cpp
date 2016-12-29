#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

//Creating html using a naive approach
void without_builder()
{
    //Very naive
    string text = "hello";
    string output;

    output += "<p>";
    output += text;
    output += "</p>";

    cout << output << endl;

    //Slightly less naive
    vector<string> words { "hello", "world" };
    ostringstream oss;
    oss << "<ul>";

    for(auto& x : words)
        oss << "\n  " << "<li>" << x << "</li>";
    oss << "\n</ul>";

    cout << oss.str() << endl;
}

/*
 * Bad: Highly coupled to the elements you are creating.
 * Not extensible.
 * Hard to test as you need a new test for each new element added.
 * Duplication of html element tags.
 * Not object orientated; html elements arent represented by objects even though they could be.
 */
