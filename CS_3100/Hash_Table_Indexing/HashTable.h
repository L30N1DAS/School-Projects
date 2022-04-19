# pragma once

#define MAXHASH 20

#include <vector>
#include <iostream>
#include "Slot.h"

using namespace std;

class HashTable {

public:

    HashTable();

    ~HashTable();

    bool insert(int, int, int&);

    bool remove(int);

    bool find(int, int&);

    float alpha();

    friend ostream& operator<<(ostream&, const HashTable&);

private:

    Slot slots[MAXHASH];
    vector<int> offsets;
    int usedSlots;
};