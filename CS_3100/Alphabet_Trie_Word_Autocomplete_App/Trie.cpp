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
    // initializes the member data
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
    DestructorHelper(root); // recursively deletes every node in the trie
}

//----------------------------------------------------------------
// DestructorHelper: used by the Destructor to delete the trie
//      Returns: none
//      Parameters:
//          current (TrieNode*) - pointer to the nodes of the trie
//----------------------------------------------------------------
void Trie::DestructorHelper(TrieNode* current) {
    // does nothing if the node does not exist
    if (current == NULL) {
        return;
    }

    // recursively traverses the trie and deletes the nodes
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
    // Local variables
    TrieNode* current;          // a pointer to the nodes corresponding to the letters of the word to be added

    current = root;

    // determines the index corresponding to each letter in the word
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        int slot = letter - 'a';
        // creates a new node at that index if one does not already exist
        if (current->pointers[slot] == NULL) {
            current->pointers[slot] = new TrieNode;
            current = current->pointers[slot];
            numNodes++;
        }
        // goes to the node at that index if one does already exist
        else {
            current = current->pointers[slot];
        }
    }

    // if the node is not already the end of a word,
    // makes it the end of a word, increments the total number of words, and 
    // determines that the given word was inserted successfully
    if (current->endOfWord == false) {
        numWords++;
        current->endOfWord = true;
        return true;
    }
    // if the node is already the end of a word (i.e., the given word is already in the trie),
    // determines that the given word was not inserted successfully
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
    // Local variables
    TrieNode* current;          // a pointer to the nodes corresponding to the letters of the word to be checked

    current = root;

    // determines the index corresponding to each letter in the word
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        int slot = letter - 'a';
        // determines that the given word is not in the trie
        // if a node does not already exist at the desired index
        if (current->pointers[slot] == NULL) {
            return false;
        }
        // goes to the node at that index if one does already exist
        else {
            current = current->pointers[slot];
        }
    }

    // determines that the given word is not in the trie
    // if the node is not already the end of a word
    if (current->endOfWord == false) {
        return false;
    }
    // determines that the given word is in the trie
    // if the node is already the end of a word
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
    // Local variables
    TrieNode* current;          // a pointer to the nodes corresponding to the letters of the given prefix
    int count;                  // an integer holding the number of words in the trie that begin with the given prefix

    current = root;
    count = 0;

    // determines the index corresponding to each letter in the word
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        int slot = letter - 'a';
        current = current->pointers[slot];
        // determines that no words begin with the given prefix
        // if a node does not already exist at the desired index
        if (current == NULL) {
            return 0;
        }
    }

    return completeCountHelper(count, current); // recursively counts the number of words in the trie
                                                // that begin with the given prefix
}

//-----------------------------------------------------------------------------------------------------
// completeCountHelper: used by the completeCount function to determine the number of words in the trie
//                      that begin with the given prefix
//      Returns: the number of words in the trie that begin with the given prefix
//      Parameters:
//          count (int&) - a reference to an integer holding the number of words in the trie
//                         that begin with the given prefix
//          current (TrieNode*) - a pointer to the nodes of the trie
//-----------------------------------------------------------------------------------------------------
int Trie::completeCountHelper(int& count, TrieNode* current) {
    // returns the number of words in the trie that begin with the given prefix
    // if the node does not exist
    if (current == NULL) {
        return count;
    }

    // recursively traverses the trie extending from the last node reached from the given prefix
    for (int i = 0; i < 26; i++) {
        completeCountHelper(count, current->pointers[i]);
    }

    // increments the total number of words in the trie that begin with the given prefix
    // if the node is the end of a word
    if (current->endOfWord == true) {
        count++;
    }

    return count;
}

//-----------------------------------------------------------------------------------------
// complete: determines which words in the trie begin with the given prefix
//      Returns: a vector containing the words in the trie that begin with the given prefix
//      Parameters:
//          word (string) - the given prefix
//-----------------------------------------------------------------------------------------
vector<string> Trie::complete(string word) {
    // Local variables
    TrieNode* current;          // a pointer to the nodes corresponding to the letters of the given prefix
    vector<string> completions; // a vector containing the words in the trie that begin with the given prefix

    current = root;

    // determines the index corresponding to each letter in the word
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        int slot = letter - 'a';
        current = current->pointers[slot];
        // determines that no words begin with the given prefix
        // if a node does not already exist at the desired index
        if (current == NULL) {
            return completions;
        }
    }

    return completeHelper(word, completions, current); // recursively collects the words in the trie
                                                       // that begin with the given prefix
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
    // returns the vector of words in the trie that begin with the given prefix
    // if the node does not exist
    if (current == NULL) {
        return completions;
    }

    // adds the word to the vector if the node corresponding to the last letter is the end of a word
    if (current->endOfWord == true) {
        completions.push_back(word);
    }

    // recursively traverses the trie extending from the last node reached from the given prefix
    for (int i = 0; i < 26; i++) {
        char letter = i + 'a';
        completeHelper(word+letter, completions, current->pointers[i]);
    }

    return completions;
}