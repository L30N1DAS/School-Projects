#pragma once
#include <string>

using namespace std;

class Character {
private:
    // Fields (more information in character.cpp)
    string name;
    string role;
    int hitPoints;
    int attackBonus;
    int damageBonus;
    int armorClass;

public:
    // Constructor
    Character(string, string, int, int, int, int);

    // print character stats
    void print(ostream&);

    // attack other character
    void attack(Character&, ostream&);

    // inflict damage
    void damage(int);

    // return current health
    int getHealth();

    // return name
    string getName();

    // return role
    string getRole();
};