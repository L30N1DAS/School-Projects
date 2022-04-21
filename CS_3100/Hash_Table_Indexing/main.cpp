#include "Database.h"
#include <iostream>
#include <string> // maybe


using namespace std;

int main() {
    Database database;
    Record record;
    int collisions;
    string action;
    string lastName;
    string firstName;
    int uid;
    string year;

    while (true) {
        cout << "Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (P)rint the database, or (Q)uit?" << endl;
        cout << "Enter action: ";
        cin >> action;

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

        else if (action == "P") {
            cout << database << endl;
        }

        else if (action == "Q") {
            cout << "Exiting." << endl;
            return 0;
        }

        else {
            continue;
        }

        cout << endl;
    }
}