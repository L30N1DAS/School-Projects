#include "AVLTree.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    AVLTree tree;

    tree.insert(100, "one hundred");
    cout << tree << endl << endl;

    tree.insert(50, "seventy-five");
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

    //cout << tree.find(125, "one") << endl;
    //cout << tree << endl;

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
}