#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Model.hpp"

/*
 * Explanation for the static visitor are in the Model.hpp file
 * 
 * Here the ostringstream oss acts as a "visitor", the for_each passes the visiting ostringstream to each element, allowing them to
 * print out their contents in HTML format.
 */

using namespace std;

void test_static_visitor()
{
    Paragraph paragraph{"Below are some colours"};
    ListItem red{"red"};
    ListItem green{"green"};
    ListItem blue{"blue"};
    List list{red, green, blue};

    vector<Element*> document{&paragraph, &list};
    ostringstream oss;


    // Print elements in HTML
    for_each(begin(document), end(document), [&] (Element* ele)
    {
        ele->print(oss);
    });

    cout << oss.str() << endl;
}
