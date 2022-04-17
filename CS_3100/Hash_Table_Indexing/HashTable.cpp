#include "HashTable.h"
#include "hashfunction.h"
#include <algorithm>
#include <array>
#include <random>
#include <chrono>  
#include <vector>

#define MAXHASH 20

HashTable::HashTable() {
    usedSlots = 0;
    for (int i = 0; i < MAXHASH; i++) {
        slots[i] = new Slot();
    }

    for (int i = 0; i < MAXHASH - 1; i++) {
        offsets.push_back(i + 1);
        // cout << offsets[i] << endl;
    }

    // Work Cited: https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
    auto rd = std::random_device{}; 
    auto rng = std::default_random_engine{rd()};
    std::shuffle(offsets.begin(), offsets.end(), rng);
    // random_shuffle(std::begin(offsets), std::end(offsets));
    // std::random_shuffle(offsets.begin(), offsets.end());
    // unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // shuffle (offsets.begin(), offsets.end(), std::default_random_engine(seed));
   // std::srand(std::time(0)); // https://stackoverflow.com/questions/14221763/stdrandom-shuffle-produces-same-result-each-time
    //random_shuffle(&offsets[0], &offsets[MAXHASH - 1]); // https://stackoverflow.com/questions/14720134/is-it-possible-to-random-shuffle-an-array-of-int-elements
    //random_shuffle(offsets.begin(), offsets.end();
    // for (int i = 0; i < MAXHASH - 1; i++) {
    //     cout << offsets[i] << endl;
    // }
    // End Work Cited
}

HashTable::~HashTable() {
    for (int i = 0; i < MAXHASH; i++) {
        delete slots[i];
    }
}

bool HashTable::insert(int key, int index, int& collisions) {

    // int currentKey = slots[hash]->getKey();
    // int currentHash = jsHash(currentKey) % 20;

    int currentProbe = 0;

    for (int i = 0; i < MAXHASH; i++) {
        int hash = ((jsHash(key) % 20) + currentProbe) % 20;
        int currentKey = slots[hash]->getKey();
        // int currentHash = jsHash(currentKey) % 20;

        // duplicate
        if (key == currentKey && slots[hash]->isNormal()) {
            return false;
        }

        // collision
        else if (slots[hash]->isNormal()) {
            collisions++;
            currentProbe = offsets[i]; // possibly out of bounds (loop should end before it matters)
        }

        // insert
        else {
            delete slots[hash];
            slots[hash] = new Slot(key, index);
            usedSlots++;
            return true;
        }
    }

    return false;
}

// test this
bool HashTable::remove(int key) {
    int currentProbe = 0;

    for (int i = 0; i < MAXHASH; i++) {
        int hash = ((jsHash(key) % MAXHASH) + currentProbe) % MAXHASH;
        int currentKey = slots[hash]->getKey();

        if (key == currentKey && slots[hash]->isNormal()) {
            slots[hash]->kill();
            usedSlots--;
            return true;
        }

        // else if (key == currentKey && slots[hash]->isNormal() == false) {
        //     return false;
        // }

        else {
            currentProbe = offsets[i];
        }
    }

    return false;
}

bool HashTable::find(int key, int& index) {
    int currentProbe = 0;

    for (int i = 0; i < MAXHASH; i++) {
        int hash = ((jsHash(key) % 20) + currentProbe) % 20;
        int currentKey = slots[hash]->getKey();

        if (key == currentKey && slots[hash]->isNormal()) {
            index = slots[hash]->getIndex();
            return true;
        }

        else {
            currentProbe = offsets[i];
        }
    }

    return false;
}

float HashTable::alpha() {
    return (usedSlots * 1.00) / MAXHASH;
}

ostream& operator<<(ostream& os, const HashTable& me) {
    os << "HashTable contents:" << endl;
    for (int i = MAXHASH - 1; i >= 0; i--) {
        if (me.slots[i]->isNormal()) {
            os << "HashTable Slot " << i << ": Key = " << me.slots[i]->getKey() << ", Index = " << me.slots[i]->getIndex() << endl; 
        }
    }
    return os;
}

// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 | 20
// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 | 19

// what if key is inserted on second probe, first probe key is removed, and key is reinserted at first probe position