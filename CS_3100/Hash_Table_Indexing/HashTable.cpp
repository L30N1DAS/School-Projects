#include "HashTable.h"
#include "hashfunction.h"
#include <random>

//------------------------------------------
// HashTable: Constructor for the hash table
//      Returns: none
//      Parameters: none
//------------------------------------------
HashTable::HashTable() {
    usedSlots = 0;

    // fills the vector of offsets
    for (int i = 0; i < MAXHASH - 1; i++) {
        offsets.push_back(i + 1);
    }

    // shuffles the vector of offsets
    // Work Cited: https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
    auto rd = random_device{}; 
    auto rng = default_random_engine{rd()};
    shuffle(offsets.begin(), offsets.end(), rng);
    // End Work Cited
}

//------------------------------------------
// ~HashTable: Destructor for the hash table
//      Returns: none
//      Parameters: none
//------------------------------------------
HashTable::~HashTable() {}

//-----------------------------------------------------------------------------------------------------------------
// insert: inserts a new key/index pair corresponding to a student record into the hash table
//      Returns: true if the key/index pair is sucessfully inserted into the hash table and false otherwise
//      Parameters:
//          key (int) - the UID of the student record to be inserted
//          index (int) - the index of the the student record in the vector of student records
//          collisions (int&) - a reference to an integer holding the number of times the hash table must be probed
//-----------------------------------------------------------------------------------------------------------------
bool HashTable::insert(int key, int index, int& collisions) {
    // Local variables
    int currentProbe;   // the offset being used for probing
    int hash;           // the hash of the key with the offset

    // if an entry in the hash table that corresponds to a student record with the provided UID already exists in the hash table,
    // determines that the provided key/index pair cannot be inserted into the hash table
    if (find(key, index, collisions) == true) {
        return false;
    }

    collisions = 0;
    currentProbe = 0;

    // loops for each of the slots in the hash table
    for (int i = 0; i < MAXHASH; i++) {
        hash = ((jsHash(key) % MAXHASH) + currentProbe) % MAXHASH;

        // if the slot at index "hash" of the hash table already contains a key/index pair,
        // probes the hash table
        if (slots[hash].isNormal()) {
            collisions++;
            currentProbe = offsets[i];
        }

        // otherwise, inserts the key/index pair in the slot at index "hash" of the hash table
        else {
            slots[hash].setKey(key);
            slots[hash].setIndex(index);
            slots[hash].setNormal();
            usedSlots++;
            return true;
        }
    }

    return false;
}

//--------------------------------------------------------------------------------------------------------
// remove: removes an entry from the hash table that corresponds to a student record with the provided UID
//      Returns: true if the entry is removed and false otherwise
//      Parameters: 
//          key (int) - the UID of the student record corresponding to the hash table entry to be removed
//--------------------------------------------------------------------------------------------------------
bool HashTable::remove(int key) {
    // Local variables
    int currentProbe;   // the offset being used for probing
    int hash;           // the hash of the key with the offset
    int currentKey;     // the key currently in the slot at index "hash" of the hash table

    currentProbe = 0;

    // loops for each of the slots in the hash table
    for (int i = 0; i < MAXHASH; i++) {
        hash = ((jsHash(key) % MAXHASH) + currentProbe) % MAXHASH;
        currentKey = slots[hash].getKey();

        // if the slot at index "hash" of the hash table already contains a key/index pair
        // and the key currently in the slot at index "hash" is the same as the provided key,
        // removes the key/index pair from the hash table
        if (key == currentKey && slots[hash].isNormal()) {
            slots[hash].kill();
            usedSlots--;
            return true;
        }

        // if the slot at index "hash" of the hash table has always been empty,
        // determines that key/index pair is not in the hash table
        else if (slots[hash].isEmptySinceStart()) {
            return false;
        }

        // otherwise, probes the hash table
        else {
            currentProbe = offsets[i];
        }
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------
// find: determines whether an entry in the hash table that corresponds to a student record with the provided UID exists
//      Returns: true if such an entry is found and false otherwise
//      Parameters:
//          key (int) - the UID of the student record corresponding to the hash table entry to be found
//          index (int&) - a reference to an integer holding the index of the the student record in the vector of student records
//          collisions (int&) - a reference to an integer holding the number of times the hash table must be probed
//-------------------------------------------------------------------------------------------------------------------------------
bool HashTable::find(int key, int& index, int& collisions) {
    // Local variables
    int currentProbe;   // the offset being used for probing
    int hash;           // the hash of the key with the offset
    int currentKey;     // the key currently in the slot at index "hash" of the hash table

    collisions = 0;
    currentProbe = 0;

    // loops for each of the slots in the hash table
    for (int i = 0; i < MAXHASH; i++) {
        hash = ((jsHash(key) % MAXHASH) + currentProbe) % MAXHASH;
        currentKey = slots[hash].getKey();

        // if the slot at index "hash" of the hash table already contains a key/index pair
        // and the key currently in the slot at index "hash" is the same as the provided key,
        // determines that an entry with the provided key already exists in the hash table
        if (key == currentKey && slots[hash].isNormal()) {
            index = slots[hash].getIndex();
            return true;
        }

        // if the slot at index "hash" of the hash table has always been empty,
        // determines that an entry with the provided key is not in the hash table
        else if (slots[hash].isEmptySinceStart()) {
            return false;
        }

        // otherwise, probes the hash table
        else {
            collisions++;
            currentProbe = offsets[i];
        }
    }

    return false;
}

//----------------------------------------------------
// alpha: calculates the load factor of the hash table
//      Returns: the load factor of the hash table
//      Parameters: none
//----------------------------------------------------
float HashTable::alpha() {
    return (usedSlots * 1.00) / MAXHASH;
}

//-----------------------------------------------------------------------
// operator<<: prints out the hash table
//      Returns: the output stream
//      Parameters:
//          os (ostream&) - a reference to the output stream
//          me (HashTable&) - a reference to the hash table being printed
//-----------------------------------------------------------------------
ostream& operator<<(ostream& os, const HashTable& me) {
    os << "HashTable contents:" << endl;
    // prints each filled slot in the hash table
    for (int i = MAXHASH - 1; i >= 0; i--) {
        if (me.slots[i].isNormal()) {
            os << "HashTable Slot " << i << ": " << me.slots[i] << endl;
        }
    }
    return os;
}

//---------------------------------------------------------------------------------
// getSlot: returns a reference to the slot in the hash table at the provided index
//      Returns: a reference to the slot in the hash table at the provided index
//      Parameters:
//          slot (int) - the index of the desired slot in the hash table
//---------------------------------------------------------------------------------
Slot& HashTable::getSlot(int slot) {
    return slots[slot];
}

//---------------------------------------------------------------------------------------------------------------------------------------
// findSlot: finds the slot in the hash table containing the provided UID
//      Returns: true if an entry in the hash table that corresponds to a student record with the provided UID exists and false otherwise
//      Parameters:
//          key (int) - the UID of the student record corresponding to the hash table slot to be found
//          slot (int&) - a reference to an integer holding the index of the slot in the hash table with the provided UID
//---------------------------------------------------------------------------------------------------------------------------------------
bool HashTable::findSlot(int key, int& slot) {
    // Local variables
    int currentProbe;   // the offset being used for probing
    int hash;           // the hash of the key with the offset
    int currentKey;     // the key currently in the slot at index "hash" of the hash table

    currentProbe = 0;

    // loops for each of the slots in the hash table
    for (int i = 0; i < MAXHASH; i++) {
        hash = ((jsHash(key) % MAXHASH) + currentProbe) % MAXHASH;
        currentKey = slots[hash].getKey();

        // if the slot at index "hash" of the hash table already contains a key/index pair
        // and the key currently in the slot at index "hash" is the same as the provided key,
        // records the index of the slot in the hash table containing the provided UID
        if (key == currentKey && slots[hash].isNormal()) {
            slot = hash;
            return true;
        }

        // if the slot at index "hash" of the hash table has always been empty,
        // determines that an entry with the provided key is not in the hash table
        else if (slots[hash].isEmptySinceStart()) {
            return false;
        }

        // otherwise, probes the hash table
        else {
            currentProbe = offsets[i];
        }
    }

    return false;
}