#include <iostream>
#include <string>
#include "character.h"

using namespace std;

int main() {

    string name;
    string role;
    int hitPoints;
    int attackBonus;
    int damageBonus;
    int armorClass;

    cout << "First character name?" << endl;
    cin >> name;

    cout << name << "'s role?" << endl;
    cin >> role;

    cout << name << " the " << role << "'s hit points?" << endl;
    cin >> hitPoints;

    cout << name << " the " << role << "'s attack bonus?" << endl;
    cin >> attackBonus;

    cout << name << " the " << role << "'s damage bonus?" << endl;
    cin >> damageBonus;

    cout << name << " the " << role << "'s armor class?" << endl;
    cin >> armorClass;

    Character character1(name, role, hitPoints, attackBonus, damageBonus, armorClass);
    character1.print(cout);


    cout << "Second character name?" << endl;
    cin >> name;

    cout << name << "'s role?" << endl;
    cin >> role;

    cout << name << " the " << role << "'s hit points?" << endl;
    cin >> hitPoints;

    cout << name << " the " << role << "'s attack bonus?" << endl;
    cin >> attackBonus;

    cout << name << " the " << role << "'s damage bonus?" << endl;
    cin >> damageBonus;

    cout << name << " the " << role << "'s armor class?" << endl;
    cin >> armorClass;

    Character character2(name, role, hitPoints, attackBonus, damageBonus, armorClass);
    character2.print(cout);
}