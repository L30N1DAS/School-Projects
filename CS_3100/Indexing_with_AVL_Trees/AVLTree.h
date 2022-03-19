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
        int leftHeight;
        int rightHeight;
		AVLTreeNode* left;
		AVLTreeNode* right;
        AVLTreeNode* parent;

		AVLTreeNode() {
			left = nullptr;
			right = nullptr;
            parent = nullptr;
		}

		AVLTreeNode(int thiskey, string thisvalue, int thisleftH, int thisrightH) {
			left = nullptr;
			right = nullptr;
			key = thiskey;
            value = thisvalue;
            leftHeight = thisleftH;
            rightHeight = thisrightH;
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

    void singleRightRotate(AVLTreeNode*&);

    void singleLeftRotate(AVLTreeNode*&);

    void doubleLeftRotate(AVLTreeNode*&);

    void doubleRightRotate(AVLTreeNode*&);



    // int getLeftHeight();

    // int getLeftHeightHelper(AVLTreeNode*&, int);

    // int getRightHeight();

    void deleteTreePostorder(AVLTreeNode*&);

    int getHeightHelper(AVLTreeNode*, int);

    int getBalance(const AVLTreeNode*);

    bool findHelper(int, string&, AVLTreeNode*&);

    vector<string> findRangeHelper(int, int, const AVLTreeNode*, vector<string>&);


    int getLeftHeight(AVLTreeNode*, int);

    int getRightHeight(AVLTreeNode*, int);

};
