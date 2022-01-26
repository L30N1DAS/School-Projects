#pragma once
#include <string>

using namespace std;

class Character {
private:
    string name;
    string role;
    int hitPoints;
    int attackBonus;
    int damageBonus;
    int armorClass;

public:
    // Constructor
    Character(string, string, int, int, int, int);

    // print
    void print(ostream&);

    // attack
    void attack(Character);

    // inflict damage
    void damage(int);

    // return current health
    int getHealth();

    // return name
    string getName();

    // return role
    string getRole();
};