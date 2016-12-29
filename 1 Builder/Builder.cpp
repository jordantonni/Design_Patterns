#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
using namespace std;

/*
 * ABSTRACT:
 * The idea behind this is to provide a builder class that provides a starting point
 * to start creating some objects along with a method to create and add more.
 * 
 * Each element has its own class, in this case HtmlElement. These form the building blocks
 * of which we are creating.
 */



// These are the building blocks that we use to build up the overall structure
struct HtmlElement
{
    string tag;
    string text;
    vector<HtmlElement> child_elements;
    const size_t indent_size = 2;

    HtmlElement()
    {}

    HtmlElement(const string& tag, const string& text)
        : tag(tag)
        , text(text)
    {}

    string str(int indent = 0)
    {
        ostringstream oss;
        string ind(indent_size * indent, ' ');
        oss << ind << "<" << tag << ">\n";

        if (text.size() > 0)
            oss << string(indent_size * (indent + 1), ' ') << text << "\n";

        for (auto& x : child_elements)
            oss << x.str(indent + 1);

        oss << ind << "</" << tag << ">" << endl;

        return oss.str();
    }
};

// Handles the creation of individual elements
struct HtmlBuilder
{
    HtmlElement root_element;

    HtmlBuilder(const string& root_tag)
    {
        root_element.tag = root_tag;
    }

    void add_child(const string& child_tag, const string& child_text)
    {
        root_element.child_elements.emplace_back(child_tag, child_text);
    }
};


void Builder()
{
    HtmlBuilder builder("ul");
    builder.add_child("li", "Eggs");
    builder.add_child("li", "Bacon");
    builder.add_child("li", "Sausage");

    cout << builder.root_element.str() << endl;
}
