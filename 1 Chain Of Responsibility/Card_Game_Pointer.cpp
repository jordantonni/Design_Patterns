#include <iostream>
#include <string>
#include <ostream>
using namespace std;

/*
 * ABSTRACT:
 * Creature cards can have their attack and defense values modified by modifiers.
 * 
 * Modifier base class has a reference to the creature it is modifying and a pointer to another Modifier.
 * Modifier add() method allows you to add another modifier to the pointer, making a linked chain of modifiers.
 * 
 * Derivied versions of modifier change some aspect of the cards in their handle method, then call the base handle.
 * Base handle() invokes the handle of the next modifier pointer, if one exists.
 * 
 * NOTE:
 * Naive way of doing this as each modifier actually changes the values of the creature permenantly. 
 */

struct Creature
{
    string name;
    int attack;
    int defense;

    Creature(const string& name, int attack, int defense)
        : name{ name }
        , attack{ attack }
        , defense{ defense }
    {}

    friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
    {
        return os
                << "name: " << obj.name
                << " attack: " << obj.attack
                << " defense: " << obj.defense;
    }

    friend bool operator==(Creature& lhs, Creature& rhs)
    {
        return lhs.name == rhs.name;
    }
};

class CreatureModifier
{
    CreatureModifier* next = nullptr;
protected:
    Creature& creature;
public:
    int id;
    static int count;

    explicit CreatureModifier(Creature& creature)
        : creature{ creature }
    {
        id = ++count;
    }

    virtual ~CreatureModifier() = default;

    void add(CreatureModifier* creature_mod)
    {
        if (creature_mod->creature == this->creature) {
            if (next) {
                next->add(creature_mod);
            }
            else {
                next = creature_mod;
            }
        }
    }

    // Could have default handle behaviour 
    // Gives each modifier an opportunity to process the creature.
    virtual void handle()
    {
        if (next)
            next->handle();
    }
};

int CreatureModifier::count = 0;

class IncreaseAttackModifier : public CreatureModifier
{
public:
    IncreaseAttackModifier(Creature& creature)
        : CreatureModifier { creature }
    {}

    void handle() override
    {
        ++creature.attack;
        CreatureModifier::handle();
    }
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
    explicit IncreaseDefenseModifier(Creature& creature)
        : CreatureModifier { creature }
    {}

    void handle() override
    {
        if (creature.attack <= 2) {
            ++creature.defense;
        }
        CreatureModifier::handle();
    }
};

class NoModify : public CreatureModifier
{
public:
    explicit NoModify(Creature& creature)
        : CreatureModifier { creature }
    { }

    // By not calling the base handle, we stop processing the chain.
    void handle() override
    { }
};


void test_cor_pointer()
{
    Creature goblin { "Goblin", 1,1, };

    CreatureModifier root { goblin };
    IncreaseAttackModifier am { goblin };
    IncreaseDefenseModifier dm { goblin };

    cout << goblin << endl;

    root.add(&am);
    root.add(&dm);


    cout << goblin << endl;
}
