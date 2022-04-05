#include "Trie.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>

#define NUM_MEM_TESTS 10000
#define MEM_TEST_SIZE 1000

void memoryLeakTest();

using namespace std;

int main() {
    cout << "Pre-memory leak test..." << endl;
    string s;
    cin >> s;

    for (int i = 0; i < NUM_MEM_TESTS; i++) {
		memoryLeakTest();
	}

	cout << "Post-memory leak test..." << endl;
    cin >> s;
}

void memoryLeakTest() {
    Trie t;
    for (int i=0; i<MEM_TEST_SIZE; i++) {
        string currentWord;

        ifstream infile;
        infile.open("wordlist.txt");

        getline(infile, currentWord);
        t.insert(currentWord);
    }
}