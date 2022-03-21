#include "AVLTree.h"
#include <iostream>
#include <string>
// #include <vector>
// #include <stdlib.h>

using namespace std;

int main() {
    AVLTree tree;

    tree.insert(100, "one hundred");
    cout << tree << endl << endl;

    tree.insert(50, "fifty");
    cout << tree << endl << endl;

    tree.insert(150, "one hundred fifty");
    cout << tree << endl << endl;

    tree.insert(75, "seventy-five");
    cout << tree << endl << endl;

    tree.insert(125, "one hundred twenty-five");
    cout << tree << endl << endl;

    AVLTree copyTree(tree);
    cout << copyTree << endl << endl;

    copyTree.insert(200, "two hundred");
    cout << tree << endl << endl;
    cout << copyTree << endl << endl;

    tree.insert(25, "twenty-five");
    cout << tree << endl << endl;
    cout << copyTree << endl << endl;

    cout << tree.insert(50, "one hundred") << endl;
    cout << tree.getHeight() << endl << endl;

    string testOr = "one";
    string &test = testOr;

    cout << tree.find(126, test) << endl;
    cout << tree << endl;

    AVLTree tree3;
    tree3.insert(1000, "one thousand");
    tree3.insert(500, "five hundred");
    tree3.insert(250, "two hundred fifty");
    cout << tree3 << endl << endl;

    cout << tree << endl;
    cout << tree3 << endl << endl;

    tree3 = tree;

    cout << tree << endl;
    cout << tree3 << endl << endl;

    tree.insert(37, "thirty-seven");
    tree3.insert(137, "one hundred thirty-seven");

    cout << tree << endl;
    cout << tree3 << endl << endl;

    
    vector<string> vec = tree.findRange(0, 14);
    // vector<int>::iterator it;
    // for (it = vec.begin(); it != vec.end(); it++) {
    //     cout << *it << endl;
    // }
    //vector<string> vec = tree.findRange(30, 200);//all of it
	// for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {	
	// 	cout << *it << endl;
	// }
    cout << "vec.size() = " << vec.size() << endl;
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << endl;
    }

    cout << tree3.getHeight() << endl << endl;


    AVLTree tree4;
    tree4.insert(3, "three");
    tree4.insert(2, "two");
    tree4.insert(1, "one");
    cout << tree4 << endl << endl;
    cout << tree4.getHeight() << endl;

    //cout << tree4.getLeftHeight() << endl;

    AVLTree tree5;
    tree5.insert(3, "three");
    cout << tree5 << endl;
    tree5.insert(1, "one");
    cout << tree5 << endl;
    tree5.insert(2, "two");
    cout << tree5 << endl;

    // 51, 25, 60, 57, 73, 22, 82, 88
    // 100, 50, 150, 25, 75, 125, 137
    // 100, 50, 300, 200, 250
    // 4, 2, 3, 1
    // 100, 300, 200, 250, 4, 2, 3, 1
    AVLTree tree6;
    tree6.insert(51, "");
    tree6.insert(25, "");
    tree6.insert(60, "");
    tree6.insert(57, "");
    tree6.insert(73, "");
    tree6.insert(22, "");
    tree6.insert(82, "");
    tree6.insert(88, "");
    cout << tree6 << endl << endl;

    AVLTree tree7;
    tree7.insert(100, "");
    tree7.insert(50, "");
    tree7.insert(150, "");
    tree7.insert(25, "");
    tree7.insert(75, "");
    tree7.insert(125, "");
    tree7.insert(137, "");
    cout << tree7 << endl << endl;

    AVLTree tree8;
    tree8.insert(100, "");
    tree8.insert(50, "");
    tree8.insert(300, "");
    tree8.insert(200, "");
    tree8.insert(250, "");
    cout << tree8 << endl << endl;

    AVLTree tree9;
    tree9.insert(4, "");
    tree9.insert(2, "");
    tree9.insert(3, "");
    tree9.insert(1, "");
    cout << tree9 << endl << endl;

    AVLTree tree10;
    tree10.insert(100, "");
    tree10.insert(300, "");
    tree10.insert(200, "");
    tree10.insert(250, "");
    tree10.insert(4, "");
    tree10.insert(2, "");
    tree10.insert(3, "");
    tree10.insert(1, "");
    cout << tree10 << endl << endl;

    AVLTree tree11;
    tree11.insert(51, "");
    tree11.insert(25, "");
    tree11.insert(60, "");
    tree11.insert(57, "");
    tree11.insert(73, "");
    tree11.insert(22, "");
    tree11.insert(82, "");
    tree11.insert(88, "");
    
    tree11.insert(78, "");
    tree11.insert(13, "");
    tree11.insert(44, "");
    tree11.insert(39, "");
    tree11.insert(81, "");
    tree11.insert(56, "");
    tree11.insert(99, "");
    tree11.insert(66, "");
    cout << tree11 << endl << endl;

}