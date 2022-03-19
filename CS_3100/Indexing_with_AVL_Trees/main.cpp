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
    tree3. insert(250, "two hundred fifty");
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
}