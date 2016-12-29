

#include <iostream>
#include <cmath>
using namespace  std;

int main() {

    int a[10];
    int sentinel = 1337;

    cout << "sentinel value:\t" << sentinel << "\n";
    *((&a[0])-1) = 7;
    cout << "sentinel value:\t" << sentinel << "\n";

    for (int i = 0; i < 10; ++i)
    {
        sentinel++;
    }

//    cout << "sentinel at memory\t\t" << &sentinel << endl;
    return 0;
}