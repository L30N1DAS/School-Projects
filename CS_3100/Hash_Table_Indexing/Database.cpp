#include "Database.h"

//---------------------------------------
// Database: Constructor for the database
//      Returns: none
//      Parameters: none
//---------------------------------------
Database::Database() {}

//---------------------------------------
// ~Database: Destructor for the database
//      Returns: none
//      Parameters: none
//---------------------------------------
Database::~Database() {}

//-----------------------------------------------------------------------------------------------------------------
// insert: inserts a new student record into the database
//      Returns: true if the student record is successfully inserted into the database and false otherwise
//      Parameters: 
//          newRecord (Record&) - a reference to the student record to be inserted into the database
//          collisions (int&) - a reference to an integer holding the number of times the hash table must be probed
//-----------------------------------------------------------------------------------------------------------------
bool Database::insert(const Record& newRecord, int& collisions) {
    // if the provided record can be inserted into the hash table,
    // inserts it into the vector of records as well
    if (indexTable.insert(newRecord.getUID(), recordStore.size(), collisions) == true) {
        recordStore.push_back(newRecord);
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------
// remove: removes the student record with the provided UID from the database
//      Returns: true if the student record is successfully removed from the database and false otherwise
//      Parameters:
//          key (int) - the UID of the student record to be removed from the database
//-------------------------------------------------------------------------------------------------------
bool Database::remove(int key) {
    // Local variables
    int index;      // the index of the student record with the provided key in the vector 
    int collisions; // the number of times the hash table must be probed
    int slot;       // the index of the slot with the provided key in the hash table 

    // if the hash table does not contain a slot corresponding to the student record with the provided UID,
    // determines that the student record cannot be removed from the database
    if (indexTable.find(key, index, collisions) == false) {
        return false;
    }

    // removes the student record from the hash table and vector of student records
    indexTable.remove(key);
    recordStore[index] = recordStore[recordStore.size() - 1];
    recordStore.pop_back();

    // if the removed student record was not the only record in the database
    // and the removed student record was not the record at the end of the vector of records,
    // updates the index in the slot of the hash table corresponding to the student record
    // now at the spot of the removed record in the vector
    if (recordStore.size() > 0 && index != recordStore.size()) {
        indexTable.findSlot(recordStore[index].getUID(), slot);
        indexTable.getSlot(slot).setIndex(index);
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
// find: determines if a student record with the provided UID exists in the database
//      Returns: true if a student record with the provided UID exists in the database and false otherwise
//      Parameters:
//          uid (int) - the UID to be searched for in the database
//          foundRecord (Record&) - a reference to the student record with the UID being searched for
//          collisions (int&) - a reference to an integer holding the number of times the hash table must be probed
//-----------------------------------------------------------------------------------------------------------------
bool Database::find(int uid, Record& foundRecord, int& collisions) {
    // Local variables
    int index;  // the index in the slot of the hash table corresponding to the student record with the provided UID

    // if an entry corresponding to a student record with the provided UID is in the hash table,
    // records the record and determines that the record is in the database
    if (indexTable.find(uid, index, collisions) == true) {
        foundRecord = recordStore[index];
        return true;
    }

    return false;
}

//---------------------------------------------------------------
// alpha: calculates the load factor of the database's hash table
//      Returns: the load factor of the database's hash table
//      Parameters: none
//---------------------------------------------------------------
float Database::alpha() {
    return indexTable.alpha();
}

//--------------------------------------------------------------------
// operator<<: prints out the database
//      Returns: the output stream
//      Parameters:
//          os (ostream&) - a reference to the output stream
//          me (Database&) - a reference to the database being printed
//--------------------------------------------------------------------
ostream& operator<<(ostream& os, Database& me) {
    // Local variables
    int recordStoreIndex;   // the index of a student record in the vector of student records

    cout << "Database contents:" << endl;
    // prints each record in the database
    for (int i = MAXHASH - 1; i >= 0; i--) {
        if (me.indexTable.getSlot(i).isNormal() == true) {
            recordStoreIndex = me.indexTable.getSlot(i).getIndex();
            os << "HashTable Slot: " << i << ", recordStore slot " << recordStoreIndex << " -- " << me.recordStore[recordStoreIndex] << endl;
        }
    }

    return os;
}