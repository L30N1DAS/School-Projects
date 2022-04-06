//---------------------------------------------------------------------------
// Name: Anmol Saini
// Project 5: Building a Word Autocomplete Application Using an Alphabet Trie
//      This file uses a trie to store words read in from a dictionary
//      and to suggest completions for the user's input.
//---------------------------------------------------------------------------

#include "Trie.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

int main() {
    // Local variables
    Trie trie;                  // a trie storing the words read in from a dictionary
    string currentWord;         // the word being read in from the dictionary
    string input;               // the word or prefix entered by the user
    string answer;              // the user's response to whether they want to view
                                // the words beginning with the input prefix
    int numCompletions;         // the number of words beginning with the input prefix
    vector<string> completions; // a vector of the words beginning with the input prefix

    ifstream(infile);
    infile.open("wordlist.txt");
    // exits the program with an error if the dictionary could not be opened or found
    if (!infile) {
        cout << "File could not be opened" << endl;
        return 1;
    }
    
    // inserts each word in the dictionary into the trie
    while (!infile.eof()) {
        getline(infile, currentWord);
        trie.insert(currentWord);
    }

    infile.close();

    // asks the user to enter a word prefix
    while (true) {
        cout << "Please enter a word prefix (or press enter to exit): ";
        getline(cin, input);
        // exits the program if the enter key is pressed
        if (input == "") {
            break;
        } 
        // outputs the number of words in the trie that begin with the input prefix
        // and asks the user if they want to view them
        else {
            numCompletions = trie.completeCount(input);
            cout << "There are " << numCompletions << " completions for the prefix '" << input << "'. Show completions? ";
            cin >> answer;
            cin.ignore(); // source: https://stackoverflow.com/questions/42818899/detecting-enter-key-in-c
            // outputs the words in the trie that begin with the input prefix
            // if they answer "Yes" or "yes" (any other answer will not output the results)
            if (answer == "Yes" || answer == "yes") {
                cout << "Completions" << endl;
                cout << "-----------" << endl;
                completions = trie.complete(input);
                for (int i = 0; i < numCompletions; i++) {
                    cout << completions[i] << endl;
                }
                cout << endl;
            }
        }
    }
}