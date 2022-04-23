# pragma once

#include "Record.h"
#include "HashTable.h"

using namespace std;

class Database {

public:

    Database();                                         // Constructor for the database

    ~Database();                                        // Destructor for the database

    bool insert(const Record&, int&);                   // inserts a new student record into the database

    bool remove(int);                                   // removes the student record with the provided UID from the database

    bool find(int, Record&, int&);                      // determines if a student record with the provided UID exists in the database

    float alpha();                                      // calculates the load factor of the database's hash table

    friend ostream& operator<<(ostream&, Database&);    // prints out the database

private:

    // Member Data
    HashTable indexTable;                               // a hash table used to find the locations of student records
                                                        // in the vector of student records
    vector<Record> recordStore;                         // a vector holding student records
};