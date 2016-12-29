#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * ABSRACT:
 * TYPE.Begin and TYPE.End are member functions of each class that return an iterator to that element.
 *  Begin(type), End(type) are global functions that delete to the memeber functions above.
 * End pointer to one past the last element.
 * 
 * *it is overloaded to return the element, ++, -- etc pointer arithmetic works on iterators.
 * Const iterators dont allow modification of the element the iterator points to.
 * 
 * rbegin(), rend(), are reverse iterators, going the opposite direction.
 * 
 * for(auto& x : things) - As long as the class type of things has a begin and end method, language for loop will work.
 * 
 */
void test_std_iterators()
{
    vector<string> names { "Jordan", "Ryan", "Rhonda", "Richard" };

    vector<string>::iterator iter = begin(names);
    cout << "First name is: " << *iter << endl;

    iter->append(" Tonni"); // Access to the underlying object
    cout << *iter << endl;

    for(auto& x : names)
        cout << x << "\t";
    cout << endl;

    vector<string>::reverse_iterator riter = rbegin(names);
    cout << "Last element is : " << *riter << endl;

    vector<string>::const_iterator citer = begin(names); // Not allowed to modify this, i.e. *citer += "appending" 


}
