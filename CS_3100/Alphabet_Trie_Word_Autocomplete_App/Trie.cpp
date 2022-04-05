//---------------------------------------------------------------------------
// Name: Anmol Saini
// Project 5: Building a Word Autocomplete Application Using an Alphabet Trie
//      This file contains the functions implemented for tries.
//---------------------------------------------------------------------------

#include "Trie.h"

//-------------------------------
// Trie: Constructor for the trie
//      Returns: none
//      Parameters: none
//-------------------------------
Trie::Trie() {
    root = new TrieNode();
    numWords = 0;
    numNodes = 1;
}

//-------------------------------
// ~Trie: Destructor for the trie
//      Returns: none
//      Parameters: none
//-------------------------------
Trie::~Trie() {
    DestructorHelper(root);
}

//----------------------------------------------------------------
// DestructorHelper: used by the Destructor to delete the trie
//      Returns: none
//      Parameters:
//          current (TrieNode*) - pointer to the nodes of the trie
//----------------------------------------------------------------
void Trie::DestructorHelper(TrieNode* current) {
    if (current == NULL) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        DestructorHelper(current->pointers[i]);
    }

    delete current;
}

//----------------------------------------------------------------------------
// insert: adds new words to the trie
//      Returns: true if the word is added to the AVL tree and false otherwise
//      Parameters:
//          word (string) - the word to be added
//----------------------------------------------------------------------------
bool Trie::insert(string word) {
    TrieNode* current = root;
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        int slot = letter - 'a';
        if (current->pointers[slot] == NULL) {
            current->pointers[slot] = new TrieNode;
            current = current->pointers[slot];
            numNodes++;
        }
        else {
            current = current->pointers[slot];
        }
    }

    if (current->endOfWord == false) {
        numWords++;
        current->endOfWord = true;
        return true;
    }
    else {
        return false;
    }
}

//-----------------------------------------------
// count: returns the number of words in the trie
//      Returns: the number of words in the trie
//      Parameters: none
//-----------------------------------------------
int Trie::count() {
    return numWords;
}

//-------------------------------------------------
// getSize: returns the number of nodes in the trie
//      Returns: the number of nodes in the trie
//      Parameters: none
//-------------------------------------------------
int Trie::getSize() {
    return numNodes;
}

//--------------------------------------------------------------------------
// find: determines if the given word is in the trie
//      Returns: true if the word is already in the trie and false otherwise
//      Parameters:
//          word (string) - the given word
//--------------------------------------------------------------------------
bool Trie::find(string word) {
    TrieNode* current = root;
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        int slot = letter - 'a';
        if (current->pointers[slot] == NULL) {
            return false;
        }
        else {
            current = current->pointers[slot];
        }
    }

    if (current->endOfWord == false) {
        return false;
    }
    else {
        return true;
    }
}

//-------------------------------------------------------------------------------------------
// completeCount: determines the number of words in the trie that begin with the given prefix
//      Returns: the number of words in the trie that begin with the given prefix
//      Parameters:
//          word (string) - the given prefix
//-------------------------------------------------------------------------------------------

int Trie::completeCount(string word) {
    TrieNode* current = root;
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        int slot = letter - 'a';
        current = current->pointers[slot];
        if (current == NULL) {
            return 0;
        }
    }
    int count = 0;
    return completeCountHelper(count, current);
}

//-------------------------------------------------------------------------------------------------
// completeCountHelper: used by completeCount function to determine the number of words in the trie
//                      that begin with the given prefix
//      Returns: the number of words in the trie that begin with the given prefix
//      Parameters:
//          count (int&) - a reference to an integer holding the number of words in the trie
//                         that begin with the given prefix
//          current (TrieNode*) - a pointer to the nodes of the trie
//-------------------------------------------------------------------------------------------------
int Trie::completeCountHelper(int& count, TrieNode* current) {
    if (current == NULL) {
        return count;
    }

    for (int i = 0; i < 26; i++) {
        completeCountHelper(count, current->pointers[i]);
    }

    if (current->endOfWord == true) {
        count++;
    }

    return count;
}

//------------------------------------------------------------------------------------
// complete: determines which words in the trie begin with the given prefix
//      Returns: a vector containing the words in the trie begin with the given prefix
//      Parameters:
//          word (string) - the given prefix
//------------------------------------------------------------------------------------
vector<string> Trie::complete(string word) {
    TrieNode* current = root;
    vector<string> completions;
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        int slot = letter - 'a';
        current = current->pointers[slot];
        if (current == NULL) {
            return completions;
        }
    }
    return completeHelper(word, completions, current);
}

//---------------------------------------------------------------------------------------------------------------
// completeHelper: used by the complete function to determine which words in the trie begin with the given prefix
//      Returns: a vector containing the words in the trie begin with the given prefix
//      Parameters:
//          word (string) - the given prefix
//          completions (vector<string>&) - a reference to a vector of type string
//                                          that holds the words in the trie that begin with the given prefix
//---------------------------------------------------------------------------------------------------------------
vector<string> Trie::completeHelper(string word, vector<string>& completions, TrieNode* current) {
    if (current == NULL) {
        return completions;
    }

    if (current->endOfWord == true) {
        completions.push_back(word);
    }

    for (int i = 0; i < 26; i++) {
        char letter = i + 'a';
        completeHelper(word+letter, completions, current->pointers[i]);
    }

    return completions;
}