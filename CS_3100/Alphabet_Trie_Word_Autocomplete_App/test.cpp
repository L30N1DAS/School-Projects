// #include "Trie.h"
// #include <iostream>

// using namespace std;

// int main() {
//     Trie trie;

//     cout << "find 'dog' = " << trie.find("dog") << endl;
//     cout << "insert 'dog' = " << trie.insert("dog") << endl;
//     cout << "insert 'dog' = " << trie.insert("dog") << endl;
//     cout << "find 'dog' = " << trie.find("dog") << endl;
//     cout << "find 'do' = " << trie.find("do") << endl;
//     cout << "find 'dogs' = " << trie.find("dogs") << endl;
//     cout << trie.count() << endl;
//     cout << trie.getSize() << endl << endl;

//     cout << "insert 'do' = " << trie.insert("do") << endl;
//     cout << "insert 'dog' = " << trie.insert("dog") << endl;
//     cout << "find 'dog' = " << trie.find("dog") << endl;
//     cout << "find 'do' = " << trie.find("do") << endl;
//     cout << trie.count() << endl;
//     cout << trie.getSize() << endl << endl;

//     vector<string> doComps = trie.complete("do");
//     cout << "do comps" << endl;
//     cout << trie.completeCount("do") << endl;
//     for (int i = 0; i < doComps.size(); i++) {
//         cout << doComps[i] << endl;
//     }
//     cout << endl;

//     vector<string> dogComps = trie.complete("dog");
//     cout << "dog comps" << endl;
//     cout << trie.completeCount("dog") << endl;
//     for (int i = 0; i < dogComps.size(); i++) {
//         cout << dogComps[i] << endl;
//     }
//     cout << endl;

//     vector<string> dogsComps = trie.complete("dogs");
//     cout << "dogs comps" << endl;
//     cout << trie.completeCount("dogs") << endl;
//     for (int i = 0; i < dogsComps.size(); i++) {
//         cout << dogsComps[i] << endl;
//     }
//     cout << endl;
// }