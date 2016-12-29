#pragma once
#include <string>
#include <vector>
#include <ostream>
/*
 * ABSTRACT:
 * Form a hierarchy of elements. Creating list items and paragraphs from text elements.
 * Element base allows us to polymorphically store a reference to all element types that constiture our entire document.
 * 
 * Each concrete Element subclass defines its print method that formats itself in HTML format into a output string stream.
 * 
 * Problems:
 *  In order to also add a markdown formatted print to each of our elements we would need to define a new print method for the base and 
 *  all subclasses
 */

struct Element
{
    virtual ~Element() = default;
    virtual void print(std::ostringstream& oss) const = 0;
};

struct TextElement : Element
{
    std::string text;

    explicit TextElement(const std::string& text)
        : text{ text }
    {}
};

struct Paragraph : TextElement
{
    explicit Paragraph(const std::string& text)
        : TextElement{ text }
    {}

    void print(std::ostringstream& oss) const override
    {
        oss << "<p> " << text << " </p>\n";
    }
};

struct ListItem : TextElement
{
    explicit ListItem(const std::string& text)
        : TextElement{ text }
    {}

    void print(std::ostringstream& oss) const override
    {
        oss << "<li> " << text << " </li>\n";
    }
};


/*
 * By inheriting from vector<ListItem> we get the inbuilt vector datastructure from *this
 * Also by using vectors initializer list we can easily create our own List of elements.
 * 
 * Important: Must also inherit from Element so that we are able to provide the print (visit()) method 
 */
struct List : std::vector<ListItem>, Element
{
    List(const ::std::initializer_list<value_type>& _Ilist)
        : vector<ListItem>{ _Ilist }
    {}

    void print(std::ostringstream& oss) const override
    {
        oss << "<ul>\n";
        for (const auto& li : *this)
            li.print(oss);
        oss << "</ul>\n";
    }
};
