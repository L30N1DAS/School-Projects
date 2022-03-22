//----------------------------------------------------------------
// Name: Anmol Saini
// Project 4: Indexing with AVL Trees
//      This file contains the functions implemented for AVL trees
//----------------------------------------------------------------

#include "AVLTree.h"
#include <exception>

//--------------------------------------
// AVLTree: Constructor for the AVL tree
//      Returns: none
//      Parameters: none
//--------------------------------------
AVLTree::AVLTree() {
    // initializes the member data
    root = NULL;
    numElts = 0;
}

//----------------------------------------------------------------------------------
// AVLTree: Copy Constructor for the AVL tree
//      Returns: none
//      Parameters:
//          a (AVLTree&) - the AVL tree off of which the new AVL tree is being based
//----------------------------------------------------------------------------------
AVLTree::AVLTree(const AVLTree& a) {
    numElts = a.numElts; // initializes the member data
    createNewTreePreorder(a.root, root); // recursively makes a node in this tree
                                         // for each node in the given tree with the same contents
}

//----------------------------------------------------------------------------------------------------
// createNewTreePreorder: used by the Copy Constructor and operator= function to duplicate an AVL tree
//      Returns: none
//      Parameters:
//          aCurrent (AVLTreeNode*) - pointer to the nodes of the old AVL tree
//          current (AVLTreeNode*&) - reference to the pointer to the nodes of the new AVL tree
//----------------------------------------------------------------------------------------------------
void AVLTree::createNewTreePreorder(const AVLTreeNode* aCurrent, AVLTreeNode*& current) {
    // does not create a new node in this tree if the corresponding node in the given tree does not exist
    if (aCurrent == NULL) {
        current = NULL;
        return;
    }
    // otherwise, creates a new node with the contents of the corresponding node in the given tree
    // and recursively traverses the left subtree and then the right subtree of both this and the given tree
    else {
        current = new AVLTreeNode(aCurrent->key, aCurrent->value, aCurrent->leftHeight, aCurrent->rightHeight);
        createNewTreePreorder(aCurrent->left, current->left);
        createNewTreePreorder(aCurrent->right, current->right);
    }
}

//--------------------------------------
// ~AVLTree: Destructor for the AVL tree
//      Returns: none
//      Parameters: none
//--------------------------------------
AVLTree::~AVLTree() {
    deleteTreePostorder(root); // recursively deletes every node in the tree
}

//-----------------------------------------------------------------------------------------
// deleteTreePostorder: used by the Destructor and operator= function to delete an AVL tree
//      Returns: none
//      Parameters:
//          current (AVLTreeNode*) - pointer to the nodes of the AVL tree
//-----------------------------------------------------------------------------------------
void AVLTree::deleteTreePostorder(AVLTreeNode* current) {
    // does nothing if the node does not exist
    if (current == NULL) {
        return;
    }
    // otherwise recursively traverses the left subtree and then the right subtree
    // and deletes the node
    else {
        deleteTreePostorder(current->left);
        deleteTreePostorder(current->right);
        delete current;
    }
}

//-------------------------------------------------------------------------------------------------
// operator=: sets an AVL tree equal to a provided AVL tree
//      Returns: a reference to the AVL tree that is being set equal to the provided AVL tree
//      Parameters:
//          a (AVLTree&) - reference to the AVL tree to which another AVL tree is being set equal
//-------------------------------------------------------------------------------------------------
AVLTree& AVLTree::operator=(const AVLTree& a) {
    deleteTreePostorder(root); // recursively deletes every node in the tree

    // sets member data to default values
    root = NULL;
    numElts = 0;

    createNewTreePreorder(a.root, root); // recursively makes a node in this tree
                                         // for each node in the given tree with the same contents
                          
    numElts = a.numElts; // initializes the member data
    return (*this);
}

//--------------------------------------------------
// getSize: returns the size of the AVL tree
//      Returns: the number of items in the AVL tree
//      Parameters: none
//--------------------------------------------------
int AVLTree::getSize() const {
    return numElts;
}

//----------------------------------------------------------------------------
// insert: adds new items to the AVL tree
//      Returns: true if the item is added to the AVL tree and false otherwise
//      Parameters:
//          key (integer) - the index or label of the item to be added
//          value (string) - the data associated with the item to be added
//----------------------------------------------------------------------------
bool AVLTree::insert(int key, string value) {
    return insertHelper(key, value, root); // creates and inserts a new node at the correct location
}

//-----------------------------------------------------------------------------------------
// insertHelper: used by the insert function to add new items to the AVL tree
//      Returns: true if the item is added to the AVL tree and false otherwise
//      Parameters:
//          key (integer) - the index or label of the item to be added
//          value (string) - the data associated with the item to be added
//          current (AVLTreeNode*&) - reference to the pointer to the nodes of the AVL tree
//-----------------------------------------------------------------------------------------
bool AVLTree::insertHelper(int key, string value, AVLTreeNode*& current) {
    // creates a new node with the desired key and value at the correct location if the are no nodes with that key
    if (current == NULL) {
        current = new AVLTreeNode(key, value, 0, 0);
        numElts++;
        return true;
    }
    // traverses the left subtree if the key of the node to be added is less than the key of the current node
    else if (key < current->key) {
        bool result = insertHelper(key, value, current->left);
        // checks for the necessity of rotations if a new node has been created and added
        if (result == true) {
            current->leftHeight = getHeightHelper(current->left, 0);
            // performs a single right rotate if current's balance is > 1 and its left child's balance is positive
            if (getBalance(current) > 1 && getBalance(current->left) > 0) {
                singleRightRotate(current);
            }
            // performs a double right rotate if current's balance is > 1 and its left child's balance is negative
            else if (getBalance(current) > 1 && getBalance(current->left) < 0) {
                doubleRightRotate(current);
            }
        }
        return result;
    }
    // traverses the right subtree if the key of the node to be added is greater than the key of the current node
    else if (key > current->key) {
        bool result = insertHelper(key, value, current->right);
        // checks for the necessity of rotations if a new node has been created and added
        if (result == true) {
            current->rightHeight = getHeightHelper(current->right, 0);
            // performs a single left rotate if current's balance is < -1 and its right child's balance is negative
            if (getBalance(current) < -1 && getBalance(current->right) < 0) {
                singleLeftRotate(current);
            }
            // performs a double left rotate if current's balance is < -1 and its right child's balance is positive
            else if (getBalance(current) < -1 && getBalance(current->right) > 0) {
                doubleLeftRotate(current);
            }
        }
        return result;
    }
    // returns false if the key of the node to be added is equal to the key of the current node
    else {
        return false;
    }
}

//----------------------------------------------------------------------------------------------------------
// singleRightRotate: performs a single right rotation to rebalance the AVL tree
//      Returns: none
//      Parameters:
//          problem (AVLTreeNode*&) - reference to the pointer to the node to be singly rotated to the right
//----------------------------------------------------------------------------------------------------------
void AVLTree::singleRightRotate(AVLTreeNode*& problem) {
    // Local variables
    AVLTreeNode* hook;              // pointer to the node to be pulled upward in the rotation process
    AVLTreeNode* tmp;               // pointer that ensures that hook's right subtree is not lost
    AVLTreeNode* problemParent;     // pointer to the parent node of the problem node

    // sets the local variables
    hook = problem->left;
    tmp = hook->right;
    problemParent = NULL;

    // determines the parent of the problem node if the problem node is not the root node
    if (problem != root) {
        problemParent = getParent(problem, root);
    }

    hook->right = problem;
    problem->left = tmp;

    if (root == problem) {
        root = hook;
    }
    else {
        if (problemParent->key > problem->key) {
            problemParent->left = hook;
        }
        else {
            problemParent->right = hook;
        }
    }
    
    hook->rightHeight = getHeightHelper(hook->right, 0);
    hook->right->leftHeight = getHeightHelper(hook->right->left, 0);
}

//---------------------------------------------------------------------------------------------------------
// singleLeftRotate: performs a single left rotation to rebalance the AVL tree
//      Returns: none
//      Parameters:
//          problem (AVLTreeNode*&) - reference to the pointer to the node to be singly rotated to the left
//---------------------------------------------------------------------------------------------------------
void AVLTree::singleLeftRotate(AVLTreeNode*& problem) {
    AVLTreeNode* hook = problem->right;
    AVLTreeNode* tmp = hook->left;

    AVLTreeNode* problemParent = NULL;

    if (problem != root) {
        problemParent = getParent(problem, root);
    }

    hook->left = problem;
    problem->right = tmp;

    if (root == problem) {
        root = hook;
    }
    else {
        if (problemParent->key < problem->key) {
            problemParent->right = hook;
        }
        else {
            problemParent->left = hook;
        }
    }

    hook->leftHeight = getHeightHelper(hook->left, 0);
    hook->left->rightHeight = getHeightHelper(hook->left->right, 0);
}

//---------------------------------------------------------------------------------------------------------
// doubleLeftRotate: performs a double left rotation to rebalance the AVL tree
//      Returns: none
//      Parameters:
//          problem (AVLTreeNode*&) - reference to the pointer to the node to be doubly rotated to the left
//---------------------------------------------------------------------------------------------------------
void AVLTree::doubleLeftRotate(AVLTreeNode*& problem) {
    singleRightRotate(problem->right);
    singleLeftRotate(problem);
}

//----------------------------------------------------------------------------------------------------------
// doubleRightRotate: performs a double right rotation to rebalance the AVL tree
//      Returns: none
//      Parameters:
//          problem (AVLTreeNode*&) - reference to the pointer to the node to be doubly rotated to the right
//----------------------------------------------------------------------------------------------------------
void AVLTree::doubleRightRotate(AVLTreeNode*& problem) {
    singleLeftRotate(problem->left);
    singleRightRotate(problem);
}

//-------------------------------------------------------------------------------------
// getParent: returns a pointer to the parent node of a specified node in thw AVL tree
//      Returns: pointer to the parent node of a specified node
//      Parameters:
//          child (AVLTreeNode*) - pointer to the node whose parent is being determined
//          current (AVLTreeNode*) - pointer to the nodes of the AVL tree
//-------------------------------------------------------------------------------------
AVLTree::AVLTreeNode* AVLTree::getParent(const AVLTreeNode* child, AVLTreeNode* current) const {
    if (current == NULL) {
        return NULL;
    }
    else {
        if (child->key < current->key) {
            if (current->left->key == child->key) {
                return current;
            }
            else {
                return getParent(child, current->left);
            }
        }
        else if (child->key > current->key) {
            if (current->right->key == child->key) {
                return current;
            }
            else {
                return getParent(child, current->right);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------
// find: retrieves the value in a specified node and puts it in a specified string
//      Returns: true if the value is retrieved and false otherwise
//      Parameters:
//          key (integer) - the index or label of the item being searched for in the AVL tree
//          value (string&) - reference to a string to hold the value of the specified node
//-------------------------------------------------------------------------------------------
bool AVLTree::find(int key, string& value) const {
    return findHelper(key, value, root);
}

//-----------------------------------------------------------------------------------------------------------------
// findHelper: used by the find function to retrieve the value in a specified node and put it in a specified string
//      Returns: true if the value is retrieved and false otherwise
//      Parameters:
//          key (integer) - the index or label of the item being searched for in the AVL tree
//          value (string&) - reference to a string to hold the value of the specified node
//          current (AVLTreeNode*&) - reference to the pointer to the nodes of the AVL tree
//-----------------------------------------------------------------------------------------------------------------
bool AVLTree::findHelper(int key, string& value, const AVLTreeNode* current) const {
    if (current == NULL) {
        return false;
    }
    else if (key < current->key) {
        return findHelper(key, value, current->left);
    }
    else if (key > current->key) {
        return findHelper(key, value, current->right);
    }
    else {
        value = current->value;
        return true;
    }
}

//-------------------------------------------------
// getHeight: calculates the height of the AVL tree
//      Returns: the height of the AVL tree
//      Parameters: none
//-------------------------------------------------
int AVLTree::getHeight() const {
    return getHeightHelper(root, 0) - 1;
}

//----------------------------------------------------------------------------------------------------------------------
// getHeightHelper: used by the getHeight, insertHelper, and rotate functions to calulate the height of a specified node
//      Returns: the height of the node
//      Parameters: 
//          current (AVLTreeNode*) - pointer to the node to have its height calculated
//          height (integer) - the height of the current node
//----------------------------------------------------------------------------------------------------------------------
int AVLTree::getHeightHelper(const AVLTreeNode* current, int height) const {
    if (current == NULL) {
        return 0;
    }
    else {
        int leftHeight = getHeightHelper(current->left, height);
        int rightHeight = getHeightHelper(current->right, height);
        if (leftHeight >= rightHeight) {
            return leftHeight+1;
        }
        else if (rightHeight > leftHeight) {
            return rightHeight+1;
        }
    }
}

//-------------------------------------------------------------------------------------
// getBalance: calulates the balance of a specified node
//      Returns: the balance of the node
//      Parameters:
//          current (AVLTreeNode*) - pointer to the node to have its balance calculated
//-------------------------------------------------------------------------------------
int AVLTree::getBalance(const AVLTreeNode* current) const {
    return current->leftHeight - current->rightHeight;
}

//-----------------------------------------------------------------
// operator<<: prints out the AVL tree
//      Returns: the output stream
//      Parameters:
//          os (ostream&) - reference to the output stream
//          me (AVLTree&) - reference to the AVL tree being printed
//-----------------------------------------------------------------
ostream& operator<<(ostream& os, const AVLTree& me) {
    int level = 0;
    me.printPreorder(os, me.root, level);
    return os;
}

//--------------------------------------------------------------------------------------------------------
// findRange: finds all values of the AVL tree with keys that fall between two specified numbers inclusive
//      Returns: a vector containing all the string values of the AVL tree
//               with keys falling between two specified numbers inclusive
//      Parameters:
//          lowkey (integer) - the lower bound
//          highkey (integer) - the upper bound
//--------------------------------------------------------------------------------------------------------
vector<string> AVLTree::findRange(int lowkey, int highkey) const {
    vector<string> range;
    return findRangeHelper(lowkey, highkey, root, range);
}

//-----------------------------------------------------------------------------------------------
// findRangeHelper: used by the findRange function to find all values of the AVL tree
//                  with keys falling between two specified numbers inclusive
//      Returns: a vector containing all the string values of the AVL tree
//               with keys falling between two specified numbers inclusive
//      Parameters:
//          lowkey (integer) - the lower bound
//          highkey (integer) - the upper bound
//          current (AVLTreeNode*) - pointer to the nodes of the AVL tree
//          range (vector<string>&) - reference to a vector of type string
//                                    holding all values of the AVL tree meeting the requirements
//-----------------------------------------------------------------------------------------------
vector<string> AVLTree::findRangeHelper(int lowkey, int highkey, const AVLTreeNode* current, vector<string>& range) const {
    if (current == NULL) {
        return range;                                                                                                                
    }
    if (current->key >= lowkey && current->key <= highkey) {
        range.push_back(current->value);
    }
    findRangeHelper(lowkey, highkey, current->left, range);
    findRangeHelper(lowkey, highkey, current->right, range);
    return range;

}

//--------------------------------------------------------------------------------------------
// printPreorder: used by the operator<< function to print out the AVL tree
//      Returns: none
//      Parameters:
//          os (ostream&) - reference to the output stream
//          current (AVLTreeNode*) - pointer to the nodes of the AVL tree
//          level (integer) - records the depth of the tree to print the correct numer of tabs
//--------------------------------------------------------------------------------------------
void AVLTree::printPreorder(ostream& os, const AVLTreeNode* current, int level) const {
    if (current == NULL) {
        return;
    }
    else {
        printPreorder(os, current->right, level+1);

        for (int i = 0; i < level; i++) {
            os << "\t";
        }
    }

    os << current->key << ", " << current->value << endl;
    printPreorder(os, current->left, level+1);
}