#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class AVLTree {
public:

    AVLTree();

    AVLTree(const AVLTree& a);

    // void copyConstructorHelper(const AVLTree&, AVLTreeNode&);

    ~AVLTree();

    bool insert(int, string);

    int getHeight();

    int getSize();

    bool find(int, string&);

    vector<string> findRange(int, int);

    friend ostream& operator<<(ostream&, const AVLTree&);

    AVLTree& operator=(const AVLTree& a);

    
private:

    class AVLTreeNode {
	public:
        int key;
        string value;
		AVLTreeNode* left;
		AVLTreeNode* right;
		int leftHeight;
        int rightHeight;
        AVLTreeNode* parent;

		AVLTreeNode() {
			left = nullptr;
			right = nullptr;
            parent = nullptr;
		}

		AVLTreeNode(int thiskey, string thisvalue, int thisleftHeight, int thisrightHeight) {
			left = nullptr;
			right = nullptr;
			key = thiskey;
            value = thisvalue;
            leftHeight = thisleftHeight;
            rightHeight = thisrightHeight;
            parent = nullptr;
		}

		~AVLTreeNode() {};

	};

    AVLTreeNode* root;
    unsigned int numElts;

    //void print(ostream&, const AVLTreeNode*) const;

    void printPreorder(ostream&, const AVLTreeNode*, int) const;

    void createNewTreePreorder(const AVLTreeNode*, AVLTreeNode*&);

    bool insertHelper(int, string, AVLTreeNode*&);

    int getLeftHeight();

    int getLeftHeightHelper(AVLTreeNode*&, int);

    int getRightHeight();

    void deleteTreePostorder(AVLTreeNode*&);

    int getHeightHelper();

    bool findHelper(int, string&, AVLTreeNode*&);
};
