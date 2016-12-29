#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
using namespace std;

/*
 * ABSTRACT:
 * The idea here is to be able to chain method calls together and add more elements via 
 * add_child().add_child().add_child() etc. -- Results in more readable code.
 * 
 * Cast operator from the builder to the element it is responsbible for building.
 * Allowing us to create a static build function within the element and start building 
 * directly from there without having to create a builder object explicity ourselves. 
 * 
 * The cast operator is then used to store the builder as an element object.
 * 
 */

struct HtmlBuilder;

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

    static HtmlBuilder build(const string& tag_name);
    static unique_ptr<HtmlBuilder> build_unique(const string& tag_name);
};

// Handles the creation of individual elements
struct HtmlBuilder
{
    HtmlElement root_element;

    HtmlBuilder(const string& root_tag)
    {
        root_element.tag = root_tag;
    }

    // Returning *this allows us to chain add_child() method invocations together
    HtmlBuilder& add_child(const string& child_tag, const string& child_text)
    {
        root_element.child_elements.emplace_back(child_tag, child_text);
        return *this;
    }

    // Allows us to convert the builder into the type of element it builds
    operator HtmlElement() const
    {
        return root_element;
    }
};

// Static method within the element class, allows us create a builder
// and start building elements without having to create the builder explicity.
HtmlBuilder HtmlElement::build(const string& root_tag_name)
{
    return HtmlBuilder(root_tag_name);
}

void FluentBuilder()
{
    HtmlBuilder builder("ul");
    builder.add_child("li", "Eggs");
    builder.add_child("li", "Bacon");
    builder.add_child("li", "Sausage");

    //    cout << builder.root_element.str() << endl;

    // the cast operator from builder to element allows us to store the builder in the htmlelement here!
    HtmlElement ele = HtmlElement::build("ul").add_child("li", "item 1").add_child("li", "item 2");
    cout << ele.str() << endl;
}
