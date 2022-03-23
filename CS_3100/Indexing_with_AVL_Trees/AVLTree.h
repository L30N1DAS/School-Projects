//--------------------------------------------------------------
// Name: Anmol Saini
// Project 4: Indexing with AVL Trees
//      This file contains the functions declared for AVL trees.
//--------------------------------------------------------------

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class AVLTree {

public:

    AVLTree();                                              // Constructor for the AVL tree

    AVLTree(const AVLTree& a);                              // Copy Constructor for the AVL tree

    ~AVLTree();                                             // Destructor for the AVL tree

    AVLTree& operator=(const AVLTree& a);                   // sets an AVL tree equal to a provided AVL tree

    bool insert(int, string);                               // adds new items to the AVL tree

    int getHeight() const;                                  // calculates the height of the AVL tree

    bool find(int, string&) const;                          // retrieves the value in a specified node
                                                            // and puts it in a specified string

    vector<string> findRange(int, int) const;               // finds all values of the AVL tree with keys
                                                            // that fall between two specified numbers inclusive

    int getSize() const;                                    // returns the size of the AVL tree

    friend ostream& operator<<(ostream&, const AVLTree&);   // prints out the AVL tree
    
private:

    // private inner class for AVL tree nodes
    class AVLTreeNode {
	public:
        int key;
        string value;
        int leftHeight;
        int rightHeight;
		AVLTreeNode* left;
		AVLTreeNode* right;

		AVLTreeNode() {
			left = nullptr;
			right = nullptr;
		}

		AVLTreeNode(int thiskey, string thisvalue, int thisleftH, int thisrightH) {
            key = thiskey;
            value = thisvalue;
            leftHeight = thisleftH;
            rightHeight = thisrightH;
			left = nullptr;
			right = nullptr;
		}

		~AVLTreeNode() {};
	};

    // Member Data
    AVLTreeNode* root;
    unsigned int numElts;

    void createNewTreePreorder(const AVLTreeNode*, AVLTreeNode*&);  // used by the Copy Constructor and operator= function
                                                                    // to duplicate an AVL tree

    void deleteTreePostorder(AVLTreeNode*);                         // used by the Destructor and operator= function
                                                                    // to delete an AVL tree

    bool insertHelper(int, string, AVLTreeNode*&);                  // used by the insert function
                                                                    // to add new items to the AVL tree

    void singleLeftRotate(AVLTreeNode*&);                           // performs a single left rotation
                                                                    // to rebalance the AVL tree

    void singleRightRotate(AVLTreeNode*&);                          // performs a single right rotation
                                                                    // to rebalance the AVL tree

    void doubleLeftRotate(AVLTreeNode*&);                           // performs a double left rotation
                                                                    // to rebalance the AVL tree

    void doubleRightRotate(AVLTreeNode*&);                          // performs a double right rotation
                                                                    // to rebalance the AVL tree

    int getHeightHelper(const AVLTreeNode*, int) const;             // used by the getHeight, insertHelper, and
                                                                    // rotate functions to calulate
                                                                    // the height of a specified node

    int getBalance(const AVLTreeNode*) const;                       // calulates the balance of a specified node

    AVLTreeNode* getParent(const AVLTreeNode*, AVLTreeNode*) const; // returns a pointer to the parent node
                                                                    // of a specified node in thw AVL tree

    bool findHelper(int, string&, const AVLTreeNode*) const;        // used by the find function to retrieve the value
                                                                    // in a specified node and put it in a specified string

    vector<string> findRangeHelper(int, int, const AVLTreeNode*,    // used by the findRange function to find all values
    vector<string>&) const;                                         // of the AVL tree with keys falling between
                                                                    // two specified numbers inclusive

    void printPreorder(ostream&, const AVLTreeNode*, int) const;    // used by the operator<< function
                                                                    // to print out the AVL tree
};