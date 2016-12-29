#include <iostream>
#include <string>
using namespace std;
#include <boost/signals2.hpp>
using namespace boost::signals2;

/*
 * ABSTRACT:
 * Broker chain seperates the command and queries. Doesnt modify the objects attributes permentantly via commands but instead
 * intercepts and changes the QUERY of asking what the attribute value is.
 * 
 * Basic idea is:
 *  - Game mediates communication between creatures and asking for their attributes.
 *  - The act of asking for an attribute is modelled by a Query, stored in the game event bus (signals)
 *  - Modifier object attaches to the bus when instantiated , specifying a function to call if the bus has any activity
 *  - When we call GetAttack from creature, it puts the attack query on the bus and the modifier object is called, returning a Query with modified attack value
 * 
 */


/*
 * Command Query Seperation:
 * 
 * We represent a query as it's own object here. Allowing us to mediate between queries and modify them.
 */
struct Query
{
    string creature_name;

    enum class Attribute
    {
        Attack,
        Defense
    } attribute;

    int value;

    Query(const string& creature_name, Attribute attribute, int value)
        : creature_name{ creature_name }
        , attribute { attribute }
        , value{ value } {}
};

// Acts as the broker / bus of communication between Creatures and modifiers. Mediator pattern.
class Game
{
public:
    signal<void(Query&)> queries;
};


class Creature2
{
    Game& game;
    int attack;
    int defense;

public:
    string name;

    Creature2(Game& game, int attack, int defense, const string& name)
        : game{ game }
        , attack{ attack }
        , defense{ defense }
        , name{ name } { }

    /*
     * Instead of just returning attack value. We place a query for the value on the Game bus.
     * Modifiers that are listening to the bus will see this query and can modify the result as required.
     */
    int GetAttack() const {
        Query query { name , Query::Attribute::Attack, attack };
        game.queries(query);
        return query.value;
    }

    friend ostream& operator<<(ostream& ost, Creature2& rhs) {
        return ost
                << "Creature:\t" << rhs.name << "\nAttack:\t\t" << rhs.GetAttack() << "\nDefense:\t" << rhs.defense << endl;
    }
};

class CreatureModifier
{
    Game& game;
    Creature2& creature;
public:
    CreatureModifier(Game& game, Creature2& creature)
        : game{ game }
        , creature{ creature } {}

    virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier
{
    connection bus_connection;
public:

    DoubleAttackModifier(Game& game, Creature2& creature)
        : CreatureModifier { game, creature } {
        bus_connection =
                game.queries.connect([&] (Query& q)
                                     {
                                         if (q.attribute == Query::Attribute::Attack && q.creature_name == creature.name)
                                         {
                                             q.value *= 2;
                                         }
                                     });
    }

    virtual ~DoubleAttackModifier() {
        bus_connection.disconnect();
    }
};


void test_broker_chain() {
    Game game;
    Creature2 strong_goblin { game, 40, 20, "Goblin" };

    cout << strong_goblin << endl;
    {
        DoubleAttackModifier dm { game, strong_goblin };
        cout << strong_goblin << endl;
    }

    cout << strong_goblin << endl;
}
