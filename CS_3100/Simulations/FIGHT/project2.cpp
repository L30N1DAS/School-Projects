//-----------------------------------------------------------------------
// Name: Anmol Saini
// Project 2: FIGHT!
//      The purpose of this project is to create two characters in an RPG
//      and to have them fight each other until one of them has died.
// Global constants and variables: none
//-----------------------------------------------------------------------

#include <iostream>
#include <string>
#include "character.h"
#include <time.h>

using namespace std;

//--------------------------------------------------------------------------
// main: creates two characters and has them take turns attacking each other
//      Returns: signal to end the program (integer)
//      Parameters: none
// -------------------------------------------------------------------------
int main() {

    // Local variables
    string name;        // The character's name
    string role;        // The character's role
    int hitPoints;      // The character's health
    int attackBonus;    // The character's default accuracy (plays a role in whether an attack connects)
    int damageBonus;    // The character's default attack power (plays a role in amount of damage dealt per attack)
    int armorClass;     // The character's evasion (plays a role in whether an attack connects)

    // creates first character based on characteristics specified by user
    cout << "First character name?" << endl;
    cin >> name;
    cout << endl;

    cout << name << "'s role?" << endl;
    cin >> role;
    cout << endl;

    cout << name << " the " << role << "'s hit points?" << endl;
    cin >> hitPoints;
    cout << endl;

    cout << name << " the " << role << "'s attack bonus?" << endl;
    cin >> attackBonus;
    cout << endl;

    cout << name << " the " << role << "'s damage bonus?" << endl;
    cin >> damageBonus;
    cout << endl;

    cout << name << " the " << role << "'s armor class?" << endl;
    cin >> armorClass;
    cout << endl;

    Character character1(name, role, hitPoints, attackBonus, damageBonus, armorClass);
    character1.print(cout);
    cout << endl;


    // creates second character based on characteristics specified by user
    cout << "Second character name?" << endl;
    cin >> name;
    cout << endl;

    cout << name << "'s role?" << endl;
    cin >> role;
    cout << endl;

    cout << name << " the " << role << "'s hit points?" << endl;
    cin >> hitPoints;
    cout << endl;

    cout << name << " the " << role << "'s attack bonus?" << endl;
    cin >> attackBonus;
    cout << endl;

    cout << name << " the " << role << "'s damage bonus?" << endl;
    cin >> damageBonus;
    cout << endl;

    cout << name << " the " << role << "'s armor class?" << endl;
    cin >> armorClass;
    cout << endl;

    Character character2(name, role, hitPoints, attackBonus, damageBonus, armorClass);
    character2.print(cout);
    cout << endl;


    srand(time(NULL)); // seeds the random number generator
    
    // loop in which turn-based combat is performed
    cout << "Simulated Combat:" << endl;
    while (true) {
        character1.attack(character2, cout); // The first character attacks the second character.
        // declares the first character the winner if the second character dies
        if (character2.getHealth() == 0) {
            cout << character1.getName() << " wins!" << endl;
            return 0;
        }
        character2.attack(character1, cout); // The second character attacks the first character.
        // declares the second character the winner if the first character dies
        if (character1.getHealth() == 0) {
            cout << character2.getName() << " wins!" << endl;
            return 0;
        }
    }

    system("pause");
}


// where to seed random/include time.h
// should characters be created in method, instead of main?
//      how would this work, since references are currently being used?
// is the infinite loop ok? handout said not to use them
// should methods not used be implemented (getRole)?