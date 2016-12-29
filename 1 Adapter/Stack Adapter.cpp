#include <vector>
#include <stack>
#include <iostream>
using namespace std;

/*
 * ABSTRACT:
 * The stack class within the standard namespace is an adapter.
 * It takes another class as the container, then provides a reduced interface to act on that container.
 * As long as the container class provides the operations required, it will work. (Duck typing)
 */

void test_stack_adapter()
{
    stack<int, deque<int>> my_stack;
    my_stack.push(5);

    cout << my_stack.top() << endl;
}