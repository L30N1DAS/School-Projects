#include "Trie.h"

Trie::Trie() {
    root = new TrieNode();
    numWords = 0;
    numNodes = 1;
}

Trie::~Trie() {

}

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
    }
}

int Trie::count() {
    return numWords;
}

int Trie::getSize() {
    return numNodes;
}

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

int Trie::completeCount(string word) {
    TrieNode* current = root;
    for (int i = 0; i < word.length(); i++) {
        char letter = word[i];
        int slot = letter - 'a';
    }
}