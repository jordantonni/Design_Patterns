#include <vector>
#include <iostream>
#include <ostream>
using namespace std;

/*
 * ABSTRACT:
 * 
 */

struct Neuron
{
    vector<Neuron*> in_connections, out_connections;
    int id;

    Neuron()
    {
        static size_t id_count = 0;
        id = ++id_count;
    }

    void connect_to(Neuron& other)
    {
        out_connections.emplace_back(&other);
        other.in_connections.emplace_back(this);
    }

    /*
     * Go through all of the neurons in the other composite type and connect them to this neuron.
     * As long as the type T defines and begin and end function, each element will be added to.
     */
    template <typename T>
    void connect_to(T& other)
    {
        for (Neuron& n : other)
            connect_to(n);
    }


    friend std::ostream& operator<<(std::ostream& os, const Neuron& obj)
    {
        for (Neuron* n : obj.in_connections)
            os << " " << n->id << "\t-->\t[" << obj.id << "]" << endl;
        for (Neuron* n : obj.out_connections)
            os << "[" << obj.id << "]\t-->\t " << n->id << endl;

        return os;
    }

    /*
     * These functions allow our single object class to act like it is a collection.
     * 
     * IMPORTANT principle to the composite design pattern.
     */
    Neuron* begin()
    {
        return this;
    }

    Neuron* end()
    {
        return this + 1;
    }
};

/*
 * Neuron layer IS-A vector. Therefore emplace_back just adds a neuron to the internal vector;
 */
struct NeuronLayer : vector<Neuron>
{
    NeuronLayer(size_t count)
    {
        while (count-- > 0){
            emplace_back(Neuron());
        }
    }

    /*
     * Connects every neuron in this vector to every neuron in whatever other collection other is.
     * Via calling the neuron classes connect_to method on each neuron iteratred.
     * 
     * Problem:
     * If other isnt a collection that provides iteration access, it will fail.
     * Therefore, to connect to just a single Neuron, we need to provide a begin() and end() function to Neuron class.
     */
    template <typename T>
    void connect_to(T& other)
    {
        for (Neuron& from : *this)
            for (Neuron& to : other)
                from.connect_to(to);
    }

    friend std::ostream& operator<<(std::ostream& os, const NeuronLayer& obj)
    {
        for (auto& n : obj)
            os << n;
        return os;
    }
};

void test_neurons()
{
    Neuron n1, n2;
    n1.connect_to(n2);

    cout << n1 << n2 << endl;

    NeuronLayer l1 { 5 };
    Neuron n3;

    l1.connect_to(n3);

    cout << n3 << endl;

    cout << l1 << endl;

}
