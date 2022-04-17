#include <iostream>
#include "HashTable.h"
// #include "hashfunction.h"


using namespace std;

int main() {
    // std::srand(std::time(0));
    // if (__cplusplus == 201703L) std::cout << "C++17\n";
    // else if (__cplusplus == 201402L) std::cout << "C++14\n";
    // else if (__cplusplus == 201103L) std::cout << "C++11\n";
    // else if (__cplusplus == 199711L) std::cout << "C++98\n";
    // else std::cout << "pre-standard C++\n";
    HashTable table;
    int collisions = 0;
    // int yay = jsHash(5);
    cout << "alpha: " << table.alpha() << endl;
    cout << table.insert(112233, 2, collisions) << endl;
    cout << "alpha: " << table.alpha() << endl;
    cout << table.insert(223344, 0, collisions) << endl;
    cout << table.insert(334455, 1, collisions) << endl;
    cout << "alpha: " << table.alpha() << endl;
    cout << table.insert(334455, 4, collisions) << endl;
    cout << "alpha: " << table.alpha() << endl;
    cout << table.insert(838294, 5, collisions) << endl;
    cout << table.insert(128429, 6, collisions) << endl;
    cout << table.insert(473821, 7, collisions) << endl;
    cout << table.insert(574388, 3, collisions) << endl;
    cout << table.insert(624695, 8, collisions) << endl;
    cout << table.insert(543731, 9, collisions) << endl;
    cout << table.insert(743829, 10, collisions) << endl;
    cout << table.insert(277652, 11, collisions) << endl;
    cout << table.insert(237432, 12, collisions) << endl;
    cout << table.insert(448321, 13, collisions) << endl;
    cout << table.insert(442555, 14, collisions) << endl;
    cout << table.insert(788288, 15, collisions) << endl;
    cout << table.insert(643728, 16, collisions) << endl;
    cout << table.insert(234566, 17, collisions) << endl;
    cout << table.insert(432626, 18, collisions) << endl;
    cout << table.insert(488382, 19, collisions) << endl;
    cout << "alpha: " << table.alpha() << endl;
    cout << table.insert(621521, 20, collisions) << endl;

    cout << "alpha: " << table.alpha() << endl;

    cout << table << endl;

    cout << table.remove(743828) << endl;
    cout << table.remove(743829) << endl;
    cout << table.remove(743829) << endl << endl;

    cout << table.alpha() << endl;
    
    cout << table << endl;
}