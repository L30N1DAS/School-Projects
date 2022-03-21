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

    ~AVLTree();

    bool insert(int, string);

    int getHeight() const;

    int getSize() const;

    bool find(int, string&) const;

    vector<string> findRange(int, int) const;

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

		AVLTreeNode() {
			left = nullptr;
			right = nullptr;
		}

		AVLTreeNode(int thiskey, string thisvalue, int thisleftH, int thisrightH) {
			left = nullptr;
			right = nullptr;
			key = thiskey;
            value = thisvalue;
            leftHeight = thisleftH;
            rightHeight = thisrightH;
		}

		~AVLTreeNode() {};
	};

    AVLTreeNode* root;
    unsigned int numElts;

    void printPreorder(ostream&, const AVLTreeNode*, int) const;

    void createNewTreePreorder(const AVLTreeNode*, AVLTreeNode*&);

    bool insertHelper(int, string, AVLTreeNode*&);

    void singleRightRotate(AVLTreeNode*&);

    void singleLeftRotate(AVLTreeNode*&);

    void doubleLeftRotate(AVLTreeNode*&);

    void doubleRightRotate(AVLTreeNode*&);

    void deleteTreePostorder(AVLTreeNode*);

    int getHeightHelper(const AVLTreeNode*, int) const;

    int getBalance(const AVLTreeNode*) const;

    bool findHelper(int, string&, const AVLTreeNode*) const;

    vector<string> findRangeHelper(int, int, const AVLTreeNode*, vector<string>&) const;

    AVLTreeNode* getParent(const AVLTreeNode*, AVLTreeNode*) const;
};