//---------------------------------------------------------------------------
// Name: Anmol Saini
// Project 5: Building a Word Autocomplete Application Using an Alphabet Trie
//      This file contains the functions declared for tries.
//---------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

using namespace std;

class Trie {

public:

    Trie();                                                             // Constructor for the trie

    ~Trie();                                                            // Destructor for the trie

    bool insert(string);                                                // adds new words to the trie

    int count();                                                        // returns the number of words in the trie

    int getSize();                                                      // returns the number of nodes in the trie

    bool find(string);                                                  // determines if the given word is in the trie

    int completeCount(string);                                          // determines the number of words in the trie
                                                                        // that begin with the given prefix

    vector<string> complete(string);                                    // determines which words in the trie begin
                                                                        // with the given prefix

private:

    // private inner class for trie nodes
    class TrieNode {
    public:
        TrieNode* pointers[26];
        bool endOfWord;

        TrieNode() {
            for (int i = 0; i < 26; i++) {
                pointers[i] = NULL;
            }
            endOfWord = false;
        }

        ~TrieNode() {}
    };

    // Member data
    TrieNode* root;             // a pointer to the first node of the trie
    unsigned int numWords;      // the number of words in the trie
    unsigned int numNodes;      // the number of nodes in the trie

    void DestructorHelper(TrieNode*);                                   // used by the Destructor to delete the trie

    int completeCountHelper(int&, TrieNode*);                           // used by the completeCount function to determine
                                                                        // the number of words in the trie
                                                                        // that begin with the given prefix

    vector<string> completeHelper(string, vector<string>&, TrieNode*);  // used by the complete function to determine
                                                                        // which words in the trie begin with the given prefix
};