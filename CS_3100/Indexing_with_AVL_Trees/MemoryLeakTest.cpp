// #include "AVLTree.h"
// #include <iostream>

// #define NUM_MEM_TESTS 10000
// #define MEM_TEST_SIZE 1000

// void memoryLeakTest();

// using namespace std;

// int main() {
//     cout << "Pre-memory leak test..." << endl;
//     string s;
//     cin >> s;

//     for (int i = 0; i < NUM_MEM_TESTS; i++) {
// 		memoryLeakTest();
// 	}

// 	cout << "Post-memory leak test..." << endl;
//     cin >> s;
// }

// void memoryLeakTest() {
//     AVLTree t;
//     for (int i=0; i<MEM_TEST_SIZE; i++) {
//         t.insert(i, "blah");
//     }
// }