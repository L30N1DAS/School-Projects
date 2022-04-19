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

ostream& operator<<(ostream& os, /*const*/ Database& me) {
    // int collisions;
    // Record currentRecord;
    int recordStoreIndex;
    cout << "Database contents:" << endl;
    for (int i = MAXHASH - 1; i >= 0; i--) {
        // me.find(me.recordStore[i].getUID(), foundRecord, collisions);
        if (me.indexTable.getSlot(i).isNormal()) {
            recordStoreIndex = me.indexTable.getSlot(i).getIndex();
            cout << "HashTable Slot: " << i << ", recordStore slot " << recordStoreIndex << " -- " << me.recordStore[recordStoreIndex];
        }
    }
}