# pragma once

#include "Record.h"
#include "HashTable.h"

using namespace std;

class Database {

public:

    Database();

    ~Database();

    bool insert(const Record&, int&);

    bool remove(int);

    bool find(int, Record&, int&);

    float alpha();

    friend ostream& operator<<(ostream&, Database&);

private:

    HashTable indexTable;
    vector<Record> recordStore;
};