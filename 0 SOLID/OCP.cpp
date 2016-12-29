#include "stdafx.h"
#pragma once

using namespace std;

enum class Color
{
    Red,
    Green,
    Blue
};

enum class Size
{
    Small,
    Medium,
    Large
};

struct Product
{
    string name;
    Color color;
    Size size;
};

/*
 * Old way of filtering. Filter class takes in a collection and has a method for each 
 * criteria that you want to filter on. Results in 2^n new filters for each combination of n criteria.
 */
struct ProductFilter
{
    typedef vector<Product*> Items;

    static Items by_color(Items& items, Color color)
    {
        Items result;

        for (auto& i : items){
            if (i->color == color)
                result.emplace_back(i);
        }
        return result;
    }

    static Items by_size(Items& items, Size size)
    {
        Items result;

        for (auto& i : items){
            if (i->size == size)
                result.emplace_back(i);
        }
        return result;
    }

    static Items by_color_and_size(Items& items, Color color, Size size)
    {
        Items result;

        for (auto& i : items){
            if (i->color == color && i->size == size)
                result.emplace_back(i);
        }
        return result;
    }
};

// --------------------------------------------------------------------------------------------//

// OCP way

/*
 * Specification interface provides an is_satisifed function.
 * Concrete implementations of the specification will implement this class for each criteria and
 * return true if the value of a collection meets the criteria
 */
template <typename T>
struct ISpecification
{
    virtual bool is_satisfied_by(T* item) = 0;
};

/*
 * Filter interface takes some collection of type T and provides a
 * filter method to apply the concrete specification on each element.
 */
template <typename T>
struct IFilter
{
    typedef vector<T*> Items;
    virtual Items filter(Items items, ISpecification<T>& spec) = 0;
};

/*
 * Concrete filter for Products. Implments the filter method by testing each
 * element of the collection against the concrete specification provided.
 */
struct BetterProductFilter : IFilter<Product>
{
    Items filter(Items items, ISpecification<Product>& spec) override
    {
        Items result;

        for (auto& elem : items)
            if (spec.is_satisfied_by(elem))
                result.emplace_back(elem);

        return result;
    }
};

/*
 * Concrete specification that tests the color of an element.
 */
struct ColorSpecification : ISpecification<Product>
{
    Color color;

    explicit ColorSpecification(Color color)
        : color(color) {}

    bool is_satisfied_by(Product* item) override
    {
        return item->color == color;
    }
};
/*
 * Concrete specification that tests the size of each element
 */
struct SizeSpecification : ISpecification<Product>
{
    Size size;

    explicit SizeSpecification(Size size)
        : size(size) {}

    bool is_satisfied_by(Product* item) override
    {
        return item->size == size;
    }
};

/*
 * Specialization of the specification interface that allows us to 
 * combine two specifications together to test each element.
 */
template <typename T>
struct ANDSpecification : ISpecification<T>
{
    ISpecification<T>& first_spec;
    ISpecification<T>& second_spec;

    ANDSpecification(ISpecification<T>& first_spec, ISpecification<T>& second_spec)
        : first_spec(first_spec)
        , second_spec(second_spec) {}

    bool is_satisfied_by(T* item) override
    {
        return first_spec.is_satisfied_by(item) && second_spec.is_satisfied_by(item);
    }
};


void OCP_TEST()
{
    Product p1{"Ball", Color::Blue, Size::Small};
    Product p2{"Tree", Color::Green, Size::Medium};
    Product p3{"House", Color::Blue, Size::Large};
    Product p4{"Car", Color::Green, Size::Medium};

    vector<Product*> products{&p1, &p2, &p3, &p4};

    BetterProductFilter filter;
    ColorSpecification colorSpec(Color::Green);
    SizeSpecification sizeSpec(Size::Medium);

    ANDSpecification<Product> andSpec(colorSpec, sizeSpec);

    auto items2 = filter.filter(products, andSpec);
    for (auto& e : items2){
        cout << e->name << " is green and med" << endl;
    }
}
