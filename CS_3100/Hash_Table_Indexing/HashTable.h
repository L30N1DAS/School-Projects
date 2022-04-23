# pragma once

#define MAXHASH 20

#include <vector>
#include <iostream>
#include "Slot.h"

using namespace std;

class HashTable {

public:

    HashTable();                                                // Constructor for the hash table

    ~HashTable();                                               // Destructor for the hash table

    bool insert(int, int, int&);                                // inserts a new key/index pair corresponding to a student record
                                                                // into the hash table

    bool remove(int);                                           // removes an entry from the hash table that corresponds
                                                                // to a student record with the provided UID

    bool find(int, int&, int&);                                 // determines whether an entry in the hash table that corresponds
                                                                // to a student record with the provided UID exists

    float alpha();                                              // calculates the load factor of the hash table

    friend ostream& operator<<(ostream&, const HashTable&);     // prints out the hash table

    Slot& getSlot(int);                                         // returns a reference to the slot in the hash table at the provided index

    bool findSlot(int, int&);                                   // finds the slot in the hash table containing the provided UID

private:

    // Member Data
    Slot slots[MAXHASH];                                        // an array of slots of size MAXHASH
    vector<int> offsets;                                        // a vector of integers containing the offsets used for probing
    int usedSlots;                                              // the number of filled slots in the hash table
};