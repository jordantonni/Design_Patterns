#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

/*
 * ABSTRACT:
 * Be able to create a complex hierarchy of objects using curly brace syntax. Where each object is created within a block.
 * 
 * Create a base class, that isnt mean to be instantaited by user code. 
 * Base class as a vector<Base> of children objects.
 * 
 * Subtypes define specific objects we can create.
 * 
 * Using initiliazer lists we can create new objects via { } and within those create new nested objects.
 * 
 */

struct Tag
{
    string name;
    string text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;

    friend ostream& operator<<(ostream& ost, const Tag& tag)
    {
        ost << "<" << tag.name;

        for (const auto& att : tag.attributes)
            ost << " " << att.first << "=\"" << att.second << "\"";

        if (tag.children.size() == 0 && tag.text.length() == 0){
            ost << "/>" << endl;
        }
        else{
            ost << ">" << endl;

            if (tag.text.length())
                ost << tag.text << endl;

            for (const auto& child : tag.children)
                ost << child;

            ost << "</" << tag.name << ">" << endl;
        }

        return ost;
    }

protected:

    Tag(const string& name, const string& text)
        : name(name)
        , text(text)
    {}


    Tag(const string& name, const vector<Tag>& children)
        : name(name)
        , children(children)
    {}
};

// Passes the initializer list of Tags into the vector of children tags.
// This allows the nested creation of more objects.
struct P : Tag
{
    explicit P(const string& text)
        : Tag("p", text)
    {}

    P(initializer_list<Tag> children)
        : Tag("p", children)
    {}
};

struct IMG : Tag
{
    explicit IMG(const string& url)
        : Tag("img", "")
    {
        attributes.emplace_back(make_pair("src", url));
    }
};

// This style of creating objects within the braces was started with the groovy programming language
void GroovyStyleBuilder()
{
    cout <<
            P {
                IMG { "http://a.com/b.png" }
            }
            << endl;
}
