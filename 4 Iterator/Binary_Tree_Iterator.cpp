#include <string>
#include <iostream>
using namespace std;

/*
 * ABSTRACT:
 * Create a Binary tree capable of holding any datatype by creating nodes and a binary tree structure that can traverse them.
 * 
 * We create a nested iterator class within the binary tree that can perform an In-order traveral (LeftChild, Root, RightChild)
 */

template <typename T>
struct BinaryTree;

template <typename T>
struct Node
{
    T value = T();
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;
    Node<T>* parent = nullptr;
    BinaryTree<T>* tree = nullptr;

    Node(const T& val)
        : value{ val }
    { }

    /*
     * Initliaize the left and right nodes, set their parent to point to this.
     */
    Node(const T& val, Node<T>* const left, Node<T>* const right)
        : value{ val }
        , left_child{ left }
        , right_child { right }
    {
        this->left_child->parent = this->right_child->parent = this;
    }

    ~Node()
    {
        if (left_child) delete left_child;
        if (right_child) delete right_child;
    }

    /*
     * Go down the tree, strating from the root and make all nodes point to the same tree structure.
     */
    void set_tree(BinaryTree<T>* t)
    {
        tree = t;
        if (left_child) left_child->set_tree(t);
        if (right_child) right_child->set_tree(t);
    }
};

template <typename T>
struct BinaryTree
{
    Node<T>* root = nullptr;

    BinaryTree(Node<T>* const root)
        : root{ root }
    {
        root->set_tree(this);
    }

    ~BinaryTree()
    {
        delete root;
    }

    /*
     * In order iterator that gives current node
     */
    template <typename U>
    struct BinaryTreeInorderIterator
    {
        Node<U>* current_node;

        explicit BinaryTreeInorderIterator(Node<U>* const current)
            : current_node { current }
        {}

        bool operator!=(const BinaryTreeInorderIterator<U>& rhs)
        {
            return current_node != rhs.current_node;
        }

        Node<U>& operator*()
        {
            return *current_node;
        }

        BinaryTreeInorderIterator<U>& operator++()
        {
            if (current_node->right_child)
            {
                current_node = current_node->right_child;
                while (current_node->left_child)
                    current_node = current_node->left_child;
            }
            else
            {
                Node<U>* parent = current_node->parent;
                while (parent && current_node == parent->right_child)
                {
                    current_node = parent;
                    parent = parent->parent;
                }
                current_node = parent;
            }
            return *this;
        }
    };

    typedef BinaryTreeInorderIterator<T> inorder_iterator;

    inorder_iterator end()
    {
        return inorder_iterator { nullptr };
    }

    inorder_iterator begin()
    {
        Node<T>* current_node = root;
        while (current_node->left_child)
            current_node = current_node->left_child;

        return inorder_iterator { current_node };
    }
};


void test_binary_tree_iterator()
{
    BinaryTree<string> family {
            new Node<string>{ "me",
                    new Node<string>{ "mother",
                        new Node<string>{ "Granny" },
                        new Node<string>{ "Granda" } },
                    new Node<string>{ "Father" }
                }
        };

    for(auto& x : family)
        cout << x.value << endl;
}
