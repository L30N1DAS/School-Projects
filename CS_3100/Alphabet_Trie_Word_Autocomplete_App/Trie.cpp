#include "Trie.h"

Trie::Trie() {
    root = new TrieNode();
    numWords = 0;
    numNodes = 1;
}

Trie::~Trie() {
    DestructorHelper(root);
}

void Trie::DestructorHelper(TrieNode* current) {
    if (current == NULL) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        DestructorHelper(current->pointers[i]);
    }

    delete current;
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
        current = current->pointers[slot];
        if (current == NULL) {
            return 0;
        }
    }
    // TrieNode* tempRoot = current;
    int count = 0;
    // if (current->endOfWord == true) {
    //     count++;
    // }
    return completeCountHelper(count, current);
}

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