//------------------------------------------------------------------------------------------------
// Name: Anmol Saini
// Project 6: Hash Table Indexing
//      This file allows a user to store and retrieve data about student records using a database.
//------------------------------------------------------------------------------------------------

#include "Database.h"

using namespace std;

int main() {
    // Local variables
    Database database;  // a database that uses hashing to access student records
    Record record;      // a student record in the database
    int collisions;     // the number of time the hash table of the database must be probed
    string action;      // the user's desired action
    string lastName;    // the last name of a student
    string firstName;   // the first name of a student
    int uid;            // the UID of a student
    string year;        // the year of a student

    // performs actions requested by the user
    while (true) {
        cout << "Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (P)rint the database, or (Q)uit?" << endl;
        cout << "Enter action: ";
        cin >> action;

        // inserts a student record into the database
        if (action == "I") {
            cout << "Inserting a new record." << endl;
            cout << "Last name: ";
            cin >> lastName;
            cout << "First name: ";
            cin >> firstName;
            cout << "UID: ";
            cin >> uid;
            cout << "Year: ";
            cin >> year;
            Record record(firstName, lastName, uid, year);

            if (database.insert(record, collisions) == true) {
                cout << "Record inserted (" << collisions << " collisions during insert)." << endl;
            }
            else {
                cout << "Record could not be inserted." << endl;
            }
        }

        // removes a student record from the database
        else if (action == "D") {
            cout << "Deleting a record." << endl;
            cout << "Enter UID: ";
            cin >> uid;

            if (database.remove(uid) == true) {
                cout << "Record deleted." << endl;
            }
            else {
                cout << "Record could not be deleted." << endl;
            }
        }

        // determines if a student record is in the database
        else if (action == "S") {
            cout << "Enter UID to search for: ";
            cin >> uid;

            if (database.find(uid, record, collisions) == true) {
                cout << "Searching... record found (" << collisions << " collisions during search)." << endl;
                cout << "---------------------------" << endl;
                cout << "Last name: " << record.getLastName() << endl;
                cout << "First name: " << record.getFirstName() << endl;
                cout << "UID: " << record.getUID() << endl;
                cout << "Year: " << record.getYear() << endl;
                cout << "---------------------------" << endl;
            }
            else {
                cout << "Searching... record not found." << endl;
            }
        }

        // prints the database and load factor
        else if (action == "P") {
            cout << database << endl;
            cout << "Load Factor of the Database: " << database.alpha() << endl;
        }

        // quits the program
        else if (action == "Q") {
            cout << "Exiting." << endl;
            return 0;
        }

        // asks the user for an action if an invalid action is requested
        else {
            continue;
        }

        cout << endl;
    }
}