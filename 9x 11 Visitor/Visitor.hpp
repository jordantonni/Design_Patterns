#pragma once
#include <string>

/*
 * Visit() method is overloaded on the type of object it has been asked to visit.
 *
 */

namespace double_dispatch
{
    struct Paragraph;
    struct ListItem;
    struct List;
}

struct Visitor
{
    virtual ~Visitor() = default;
    virtual void visit(const double_dispatch::Paragraph& paragraph) = 0;
    virtual void visit(const double_dispatch::List& paragraph) = 0;
    virtual void visit(const double_dispatch::ListItem& paragraph) = 0;
    virtual std::string str() const = 0;
};
