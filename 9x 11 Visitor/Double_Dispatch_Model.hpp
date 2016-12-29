#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Visitor.hpp"

/*
 * Element classes can accepth a visitor object.
 * They then call the visitors visit() method on themselves by passing a refernce to *this.
 * 
 * This allows the visitor to invoke the visit() method appropriate to that datatype.
 */

namespace double_dispatch
{
    struct Element
    {
        virtual ~Element() = default;
        virtual void accept(Visitor& visitor) = 0;
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

        void accept(Visitor& visitor) override
        {
            visitor.visit(*this);
        }
    };

    struct ListItem : TextElement
    {
        explicit ListItem(const std::string& text)
            : TextElement{ text }
        {}

        void accept(Visitor& visitor) override
        {
            visitor.visit(*this);
        }
    };

    struct List : std::vector<ListItem>, Element
    {
        List(const ::std::initializer_list<value_type>& _Ilist)
            : vector<ListItem>{ _Ilist }
        {}

        void accept(Visitor& visitor) override
        {
            visitor.visit(*this);
        }
    };
}
