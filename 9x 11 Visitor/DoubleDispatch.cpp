#include <string>
#include <iostream>
#include "Double_Dispatch_Model.hpp"
#include <algorithm>
#include "Visitor.hpp"
using namespace std;
using namespace double_dispatch;

/*
 * ABSTRACT:
 * Each element can be iterated though and passed in a concrete visitor object using the Elements' accept() method.
 * 
 * Accept invokes the visit() method of the HtmlVisitor, passing in a reference to itself via *this. Allowing the HtmlVisitors' overloaded visit() methods
 * to select the correct function based on if the element was a Paragraph, List or ListItem.
 * 
 */

struct HtmlVisitor : Visitor
{
    void visit(const Paragraph& paragraph) override
    {
        oss << "<p> " << paragraph.text << " </p>\n";
    }

    void visit(const List& list) override
    {
        oss << "<ul>\n";
        for(auto li : list)
            li.accept(*this);
        oss << "</ul>\n";
    }

    void visit(const ListItem& list_item) override
    {
        oss << "<li> " << list_item.text << " </li>\n";
    }

    string str() const override
    {
        return oss.str();
    }

private:
    ostringstream oss;
};


void test_double_dispatch()
{
    Paragraph paragraph { "Below are some colours" };
    ListItem red { "red" };
    ListItem green { "green" };
    ListItem blue { "blue" };
    List list { red, green, blue };

    vector<Element*> document { &paragraph, &list };

    HtmlVisitor visitor;

    for(auto ele : document)
        ele->accept(visitor);

    cout << visitor.str() << endl;


}
