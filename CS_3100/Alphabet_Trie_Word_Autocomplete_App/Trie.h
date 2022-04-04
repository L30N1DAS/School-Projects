#pragma once

#include <string>
#include <vector>

using namespace std;

class Trie {

public:

    Trie();

    ~Trie();

    bool insert(string);

    int count();

    int getSize();

    bool find(string);

    int completeCount(string);

    vector<string> complete(string);

private:

    class TrieNode {
    public:
        // TrieNode** pointers;
        TrieNode* pointers[26];
        bool endOfWord;

        TrieNode() {
            // pointers = new TrieNode*[26];
            for (int i = 0; i < 26; i++) {
                pointers[i] = NULL;
            }
            endOfWord = false;
        }

        ~TrieNode() {}
    };

    TrieNode* root;
    unsigned int numWords;
    unsigned int numNodes;

    void DestructorHelper(TrieNode*);
    int completeCountHelper(int&, TrieNode*);
    vector<string> completeHelper(string, vector<string>&, TrieNode*);

};