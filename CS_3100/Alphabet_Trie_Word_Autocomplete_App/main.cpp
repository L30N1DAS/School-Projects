#include "Trie.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

int main() {
    Trie trie;
    string currentWord;

    ifstream(infile);
    infile.open("wordlist.txt");
    if (!infile) {
        cout << "File could not be opened" << endl;
        return 1;
    }
    
    while (!infile.eof()) {
        getline(infile, currentWord);
        trie.insert(currentWord);
    }
    // cout << trie.count() << endl;

    string input;
    string answer;
    while (true) {
        cout << "Please enter a word prefix (or press enter to exit): ";
        char firstChar = cin.get();
        // http://www.cplusplus.com/forum/beginner/2624/
        if (firstChar == '\n') {
            break;
        } else {
            cin >> input;
            input = firstChar + input;
            cin.ignore(); // https://stackoverflow.com/questions/42818899/detecting-enter-key-in-c
            int numCompletions = trie.completeCount(input);
            cout << "There are " << numCompletions << " completions for the prefix '" << input << "'. Show completions? ";
            cin >> answer;
            cin.ignore();
            if (answer == "Yes" || answer == "yes") {
                cout << "Completions" << endl;
                cout << "-----------" << endl;
                vector<string> completions = trie.complete(input);
                for (int i = 0; i < numCompletions; i++) {
                    cout << completions[i] << endl;
                }
                cout << endl;
            }
        }
    }
}