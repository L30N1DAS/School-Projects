//----------------------------------------------------------------------------------------------------------------
// Name: Anmol Saini
// Project 2: FIGHT!
//      This file contains the fields and methods for the characters
// Fields:
//      name (string) - the character's name
//      role (string) - the character's role
//      hitPoints (integer) - The character's health
//      attackBonus (integer) - the character's default accuracy (plays a role in whether an attack connects)
//      damageBonus (integer) - the character's default attack power (plays a role in amount of damage dealt per attack)
//      armorClass (integer) - the character's evasion (plays a role in whether an attack connects)
//----------------------------------------------------------------------------------------------------------------

#include "character.h"
#include <iostream>
#include <stdlib.h>

//---------------------------------------------------------------------
// Character: Constructor for the character
//      Returns: none
//      Parameters: used to initialize corresponding fields
//          newName (string) - name entered by user
//          newRole (string) - role entered by user
//          newHitPoints (integer) - health entered by user
//          newAttackBonus (integer) - default accuracy entered by user
//          newDamageBonus (integer) - default damage entered by user
//          int newArmorClass (integer) - evasion entered by user
//---------------------------------------------------------------------
Character::Character(string newName, string newRole, int newHitPoints, int newAttackBonus, int newDamageBonus, int newArmorClass) {
    name = newName;
    role = newRole;
    hitPoints = newHitPoints;
    attackBonus = newAttackBonus;
    damageBonus = newDamageBonus;
    armorClass = newArmorClass;
}

//---------------------------------------------------------------------------------------
// print: outputs a summary of the character's information to the specified output stream
//      Returns: none
//      Parameters:
//          os (ostream&) - the output stream; set to cout
//---------------------------------------------------------------------------------------
void Character::print(ostream& os) {
    os << "Character summary" << endl;
    os << "-----------------" << endl;
    os << name << " the " << role << endl;
    os << "HP: " << hitPoints << endl;
    os << "AB: " << attackBonus << endl;
    os << "DB: " << damageBonus << endl;
    os << "AC: " << armorClass << endl;
}

//------------------------------------------------------------------------------------------------------------
// attack: determines if one character attacks another during the former's turn and initiates the attack if so
//      Returns: none
//      Parameters:
//          otherCharacter (Character&) - the character being attacked
//          os (ostream&) - the output stream; set to cout
//------------------------------------------------------------------------------------------------------------
void Character::attack(Character& otherCharacter, ostream& os) {

    // Local variables
    int dieTossAB;      // the character's attack bonus or accuracy buff (the result of a 20-sided die roll)
    int accuracy;       // the character's total accuracy (the sum of the character's accuracy buff and default accuracy)
    int dieTossDB;      // the character's damage bonus or attack power buff (the result of a 10-sided die roll)
    int damageAmount;   // the damage dealt by the character or the character's total attack power
                        // (the sum of the character's attack power buff and default attack power)

    os << name << " attacks!" << endl;
    dieTossAB = (rand() % 20) + 1;
    accuracy = dieTossAB + attackBonus;

    // If the character's total accuracy is greater than or equal to the opponent's evasion,
    // the attack connects.
    if (accuracy >= otherCharacter.armorClass) {
        os << "Attack roll: " << dieTossAB << " + " << attackBonus << " = " << accuracy << " --> HIT!" << endl;
        dieTossDB = (rand() % 10) + 1;
        damageAmount = dieTossDB + damageBonus;
        os << "Damage: " << dieTossDB << " + " << damageBonus << " = " << damageAmount << endl;

        // inflicts damage upon the opponent and displays the opponent's remaining health
        otherCharacter.damage(damageAmount);
        os << otherCharacter.name << " has " << otherCharacter.hitPoints << " hit points remaining" << endl;
    }

    // If the character's total accuracy is less than the opponent's evasion,
    // the attack misses.
    else {
        os << "Attack roll: " << dieTossAB << " + " << attackBonus << " = " << accuracy << " --> MISS!" << endl;
    }

    cout << endl;
}

//------------------------------------------------------------------------------
// damage: inflicts damage upon the character by reducing the character's health
//      Returns: none
//      Parameters: 
//          amount (integer) - how much damage is dealt to the character
//------------------------------------------------------------------------------
void Character::damage(int amount) {
    hitPoints = hitPoints - amount;
    if (hitPoints < 0) {
        hitPoints = 0;
    }
}

//--------------------------------------------------
// getHealth: returns the character's current health
//      Returns: the character's current health
//      Parameters: none
//--------------------------------------------------
int Character::getHealth() {
    return hitPoints;
}

//--------------------------------------
// getName: returns the character's name
//      Returns: the character's name
//      Parameters: none
//--------------------------------------
string Character::getName() {
    return name;
}

//--------------------------------------
// getRole: returns the character's role
//      Returns: the character's role
//      Parameters: none
//--------------------------------------
string Character::getRole() {
    return role;
}