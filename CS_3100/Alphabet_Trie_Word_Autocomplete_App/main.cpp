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

    bool end = false;
    string input;
    while (!end) {
        cout << "Please enter a word prefix (or press enter to exit): ";
        cin >> input;
        if (input == "\n") {
            break;
        } else {
            
        }
    }
}