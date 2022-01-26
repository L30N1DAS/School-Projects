#include "character.h"
#include <iostream>

Character::Character(string newName, string newRole, int newHitPoints, int newAttackBonus, int newDamageBonus, int newArmorClass) {
    name = newName;
    role = newRole;
    hitPoints = newHitPoints;
    attackBonus = newAttackBonus;
    damageBonus = newDamageBonus;
    armorClass = newArmorClass;
}

void Character::print(ostream& os) {
    os << "Character summary" << endl;
    os << "-----------------" << endl;
    os << name << " the " << role << endl;
    os << "HP: " << hitPoints << endl;
    os << "AB: " << attackBonus << endl;
    os << "DB: " << damageBonus << endl;
    os << "AC: " << armorClass << endl;
}