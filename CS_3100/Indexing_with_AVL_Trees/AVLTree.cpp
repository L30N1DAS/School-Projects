#include "AVLTree.h"
#include <exception>

AVLTree::AVLTree() {
    root = NULL;
    numElts = 0;
}

AVLTree::AVLTree(const AVLTree& a) {
    // this may not be necessary if the if statement in the recursive function is updated
    if (a.root == NULL) {
        root = NULL;
        return;
    }

    numElts = a.numElts;

    createNewTreePreorder(a.root, root);
}

void AVLTree::createNewTreePreorder(const AVLTreeNode* aCurrent, AVLTreeNode*& current) {
    if (aCurrent == NULL) {
        return;
    }
    else {
        current = new AVLTreeNode(aCurrent->key, aCurrent->value, aCurrent->leftHeight, aCurrent->rightHeight);
        createNewTreePreorder(aCurrent->left, current->left);
        createNewTreePreorder(aCurrent->right, current->right);
    }
}

AVLTree::~AVLTree() {
    deleteTreePostorder(root);

    root = NULL;
    numElts = 0;
}

void AVLTree::deleteTreePostorder(AVLTreeNode* current) {
    if (current == NULL) {
        return;
    }
    else {
        deleteTreePostorder(current->left);
        deleteTreePostorder(current->right);
        delete current;
    }
}

AVLTree& AVLTree::operator=(const AVLTree& a) {
    deleteTreePostorder(root);
    root = NULL;
    numElts = 0;
    createNewTreePreorder(a.root, root);
    numElts = a.numElts;
    return (*this);
}

int AVLTree::getSize() {
    return numElts;
}

bool AVLTree::insert(int key, string value) {
    return insertHelper(key, value, root);
}

bool AVLTree::insertHelper(int key, string value, AVLTreeNode*& current) {
    if (current == NULL) {
        current = new AVLTreeNode(key, value, 0, 0);
        numElts++;
        return true;
    }
    else if (key < current->key) {
        bool result = insertHelper(key, value, current->left);
        if (result == true) {
            // recalculate left height
            current->leftHeight = getHeightHelper(current->left, 0);
            // check balance
            // int currentBalance = current->leftHeight - current->rightHeight;
            // int leftChildBalance = current->left->leftHeight
            // maybe rotate
            if (getBalance(current) > 1 && getBalance(current->left) > 0) {
                singleRightRotate(current);
            }
            else if (getBalance(current) > 1 && getBalance(current->left) < 0) {
                doubleRightRotate(current);
            }
        }
        return result;
    }
    else if (key > current->key) {
        bool result = insertHelper(key, value, current->right);
        if (result == true) {
            current->rightHeight = getHeightHelper(current->right, 0);
            if (getBalance(current) < -1 && getBalance(current->right) < 0) {
                singleLeftRotate(current);
            }
            else if (getBalance(current) < -1 && getBalance(current->right) > 0) {
                doubleLeftRotate(current);
            }
        }
        return result;
    }
    else {
        return false;
    }
}

void AVLTree::singleRightRotate(AVLTreeNode*& problem) {
    AVLTreeNode* hook = problem->left;
    AVLTreeNode* tmp = hook->right;

    AVLTreeNode* problemParent = NULL;

    if (problem != root) {
        problemParent = getParent(problem, root);
    }

    hook->right = problem;
    problem->left = tmp;

    if (root == problem) {
        root = hook;
    }

    if (problemParent != NULL) {
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

    if (problemParent != NULL) {
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

void AVLTree::doubleLeftRotate(AVLTreeNode*& problem) {
    singleRightRotate(problem->right);
    singleLeftRotate(problem);
}

void AVLTree::doubleRightRotate(AVLTreeNode*& problem) {
    singleLeftRotate(problem->left);
    singleRightRotate(problem);
}

AVLTree::AVLTreeNode* AVLTree::getParent(AVLTreeNode* child, AVLTreeNode* current) {
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

bool AVLTree::find(int key, string& value) {
    return findHelper(key, value, root);
}

bool AVLTree::findHelper(int key, string& value, AVLTreeNode*& current) {
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

int AVLTree::getHeight() {
    return getHeightHelper(root, 0) - 1;
}

int AVLTree::getHeightHelper(AVLTreeNode* current, int height) {
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

int AVLTree::getBalance(const AVLTreeNode* current) {
    return current->leftHeight - current->rightHeight;
}
     
ostream& operator<<(ostream& os, const AVLTree& me) {
    int level = 0;
    me.printPreorder(os, me.root, level);
    return os;
}

vector<string> AVLTree::findRange(int lowkey, int highkey) {
    vector<string> range;
    return findRangeHelper(lowkey, highkey, root, range);
}

vector<string> AVLTree::findRangeHelper(int lowkey, int highkey, const AVLTreeNode* current, vector<string>& range) {
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