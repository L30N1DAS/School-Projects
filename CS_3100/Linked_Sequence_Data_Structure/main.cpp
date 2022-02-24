// #include <iostream>
// #include "sequence.h"

// using namespace std;

// int main() {
//     Sequence seq(5);
//     cout << seq << endl << endl;
//     cout << seq.front() << endl;
//     seq.pop_back();
//     cout << seq << endl << endl;
//     cout << seq.size() << endl << endl;
//     cout << seq.back() << endl << endl;
//     seq.push_back(10);
//     cout << seq << endl << endl;
//     cout << seq.size() << endl << endl;
//     cout << seq.back() << endl << endl << endl << endl;

//     Sequence seq2(seq);

//     cout << seq << endl;
//     cout << seq2 << endl;
//     seq.pop_back();
//     cout << seq << endl;
//     cout << seq2 << endl << endl;

//     seq2.push_back(20);
//     seq2.push_back(30);
//     seq2.push_back(40);
//     cout << seq << endl;
//     cout << seq2 << endl;
//     seq2.pop_back();
//     seq2 = seq;
//     cout << seq2.size() << endl;
//     cout << seq << endl;
//     cout << seq2 << endl;
//     seq2.pop_back();
//     cout << seq << endl;
//     cout << seq2 << endl << endl << endl;

//     seq2.pop_back();
//     cout << seq2 << endl;
//     seq2.pop_back();
//     cout << seq2 << endl;
//     seq2.pop_back();
//     cout << seq2 << endl << endl << endl;

//     // seq.insert(5, 8);
//     // cout << seq << endl;

//     Sequence seq3(5);
//     cout << seq3 << endl;
//     //seq3.erase(5, 1);
//     //seq3.insert(5, 30);
//     seq3.erase(1, 0); // issues with cuz aliveNode doesn't exit for last iteration
//     //seq3[2] = 100;
//     cout << seq3 << endl << endl << endl;

//     // seq3[-1] = 20;
//     // cout << seq3 << endl;

// }