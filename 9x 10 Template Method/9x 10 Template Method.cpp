#include <iostream>
#include <string>
using namespace std;

/*
 * ABSTRACT:
 * Skeleton of the algorithim is implemented in an abstract base class with virtual methods for the specifics.
 * 
 * Specific versions of the algorithim inherit from the base template / skeleton class and implement concrete ways to carry out the algorhithims specifics.
*/

class Game
{
public:

    explicit Game(const int num_of_players)
        : num_of_players{ num_of_players }
    {}

    // Provides the skeleton of the algorithim to run a game
    void run()
    {
        start();
        while (!have_winner())
            take_turn();

        cout << "Player " << get_winner() << " has won!\n";
    }

protected:
    int num_of_players;
    int current_player = 0;

    // Virtual methods will be implemented by subclassess
    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;
};


// Specific implementations of the methods are implemented by the chess subclass
class Chess : public Game
{
public:
    explicit Chess()
        : Game { 2 }
    {}

private:

    int turns = 0;

    void start() override
    {
        cout << "Starting a game of chess with " << num_of_players << " players." << endl;
    }

    bool have_winner() override
    {
        return turns > 10;
    }

    void take_turn() override
    {
        cout << "Player " << current_player << " taking turn " << turns << endl;
        ++turns;
        current_player = (current_player + 1) % num_of_players;
    }

    int get_winner() override
    {
        return current_player;
    }
};


int main()
{
    Chess chess;
    chess.run();
    return 0;
}
