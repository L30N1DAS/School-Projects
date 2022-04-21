#include "Database.h"

Database::Database() {}

Database::~Database() {}

bool Database::insert(const Record& newRecord, int& collisions) {
    // int index;

    // if (indexTable.find(newRecord.getUID(), index, collisions) == true) {
    //     return false;
    // }

    
    if (indexTable.insert(newRecord.getUID(), recordStore.size(), collisions) == true) {
        recordStore.push_back(newRecord);
        return true;
    }

    return false;
}

bool Database::remove(int key) {
    int index;
    int collisions;
    int slot;

    if (indexTable.find(key, index, collisions) == false) {
        return false;
    }

    indexTable.remove(key);
    
    recordStore[index] = recordStore[recordStore.size() - 1];
    recordStore.pop_back();

    if (recordStore.size() > 0 && index != recordStore.size()) {
        indexTable.findSlot(recordStore[index].getUID(), slot);
        indexTable.getSlot(slot).setIndex(index);
    }

    return true;





    // take index
    // recordStore.erase(recordStore.begin() + index);
    // recordStore[index] = recordStore[recordStore.size()-1]
    // recordStore.pop_back()
    //indexTable.find(recordStore[index].getUID(), index, collisions, slot);
    //indexTable.setIndex(recordStore[index].getUID());
    // 
}

bool Database::find(int uid, Record& foundRecord, int& collisions) {
    int index;

    if (indexTable.find(uid, index, collisions) == true) {
        foundRecord = recordStore[index];
        return true;
    }

    return false;
}

float Database::alpha() {
    return indexTable.alpha();
}

ostream& operator<<(ostream& os, Database& me) {
    // int collisions;
    // Record currentRecord;
    int recordStoreIndex;
    cout << "Database contents:" << endl;
    for (int i = MAXHASH - 1; i >= 0; i--) {
        // me.find(me.recordStore[i].getUID(), foundRecord, collisions);
        if (me.indexTable.getSlot(i).isNormal() == true) {
            recordStoreIndex = me.indexTable.getSlot(i).getIndex();
            os << "HashTable Slot: " << i << ", recordStore slot " << recordStoreIndex << " -- " << me.recordStore[recordStoreIndex] << endl;
        }
    }

    return os;
}

// removing from vector at specific index
// will vector close empty spot
// 