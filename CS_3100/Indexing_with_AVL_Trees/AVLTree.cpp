#include "AVLTree.h"
#include <exception>

AVLTree::AVLTree() {
    root = NULL;
    numElts = 0;
}

// create this, left, right
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

void AVLTree::deleteTreePostorder(AVLTreeNode*& current) {
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

// /*void AVLTree::copyConstructorHelper(const AVLTree& a, AVLTreeNode& cur) {
//     //if (a.left)
// }*/

int AVLTree::getSize() {
    return numElts;
}

// bool AVLTree::insert(int key, string value) {
//     AVLTreeNode* current;
//     AVLTreeNode* newNode;

//     current = root;

//     if (root == NULL) {
//         newNode = new AVLTreeNode(key, value, 0, 0);
//         root = newNode;
//     }

//     else if (key == current->key) {
//         return false;
//     }

//     while (current->left != NULL && current->right != NULL) {
//         if (key < current->key) {
//             current = current->left;
//         }

//         else if (key > current->key) {
//             current = current->right;
//         }

//         else if (key == current->key) {
//             return false;
//         }
//     }

//     if (current->left != NULL && key < current->key) {
//         current = current->left;
//         if (key == current->key) {
//             return false;
//         }
//     }

//     else if (current->right != NULL && key > current->key) {
//         current = current->right;
//         if (key == current->key) {
//             return false;
//         }
//     }

//     newNode = new AVLTreeNode(key, value, 0, 0);

//     if (key < current->key) {
//         current->left = newNode;
//         numElts++;
//         return true;
//     }

//     else if (key > current->key) {
//         current->right = newNode;
//         numElts++;
//         return true;
//     }
// }

bool AVLTree::insert(int key, string value) {
    // AVLTreeNode* current;
    // current = root;
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
                //doubleLeftRotate(current);
                doubleRightRotate(current);
            }
        }
        return result;
    }
    else if (key > current->key) {
        bool result = insertHelper(key, value, current->right);
        if (result == true) {
            current->rightHeight = getHeightHelper(current->right, 0);
            if (getBalance(current) > 1 && getBalance(current->right) > 0) {
                singleLeftRotate(current);
            }
            else if (getBalance(current) > 1 && getBalance(current->right) < 0) {
                //doubleRightRotate(current);
                doubleLeftRotate(current);
            }
        }
        return result;
    }
    else {
        return false;
    }
}

// recalc hook->right height on srr
// recalc hook right height
void AVLTree::singleRightRotate(AVLTreeNode*& problem) {
    AVLTreeNode* hook = problem->left;
    AVLTreeNode* tmp = hook->right;

    hook->right = problem;
    problem->left = tmp;

    if (root == problem) {
        root = hook;
    }
    
    hook->rightHeight = getHeightHelper(hook->right, 0);
    problem->leftHeight = getHeightHelper(hook->left, 0);
}

void AVLTree::singleLeftRotate(AVLTreeNode*& problem) {
    AVLTreeNode* hook = problem->right;
    AVLTreeNode* tmp = hook->left;

    hook->left = problem;
    problem->right = tmp;

    if (root == problem) {
        root = hook;
    }

    hook->leftHeight = getHeightHelper(hook->left, 0);
    problem->rightHeight = getHeightHelper(hook->right, 0);
}

// going correct way. first call does not update the problem node
void AVLTree::doubleLeftRotate(AVLTreeNode*& problem) {
    singleRightRotate(problem->right);
    singleLeftRotate(problem);
}

void AVLTree::doubleRightRotate(AVLTreeNode*& problem) {
    singleLeftRotate(problem->left);
    singleRightRotate(problem);
}

// test this and fix getHeight, getLeftHeight, and getRightHeight
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
    //return getLeftHeight();
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

/*int AVLTree::getLeftHeight(AVLTreeNode* current, int height) {
    if (current == NULL) {
        return 0;
    }
    else {
        int leftHeight = getHeightHelper(current->left, height);
        int rightHeight = getHeightHelper(current->right, height);
        return leftHeight+1;
    }
}

int AVLTree::getRightHeight(AVLTreeNode* current, int height) {
    if (current == NULL) {
        return 0;
    }
    else {
        int leftHeight = getHeightHelper(current->left, height);
        int rightHeight = getHeightHelper(current->right, height);
        return leftHeight+1;
    }
}*/

/*int AVLTree::getLeftHeight() {
    if (root == NULL) {
        return 0;
    }
    else {
    return getLeftHeightHelper(root->left, 0);
    }
}

int AVLTree::getLeftHeightHelper(AVLTreeNode*& current, int height) {
    if (current == NULL) {
        return height;
    }
    else {
        getLeftHeightHelper(current->left, height+1);
        //cout << height << endl;
    }
}

int AVLTree::getRightHeight() {

}*/

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
    
    // else if (current->key >= lowkey && current->key <= highkey) {
    //     range.push_back(current->value);
    //     findRangeHelper(lowkey, highkey, current->left, range);
    //     findRangeHelper(lowkey, highkey, current->right, range);
    //     return range;
    // }
    






    // return findRangeHelper(lowkey, highkey, current->left, range);
    // if (current->key >= lowkey && current->key <= highkey) {
    //     range.push_back(current->value);
    // }
    // return findRangeHelper(lowkey, highkey, current->right, range);
    // if (current->key >= lowkey && current->key <= highkey) {
    //     range.push_back(current->value);
    // }


    // else if (current->key >= lowkey) {
    //     range.push_back(current->value);
    //     return findRangeHelper(lowkey, highkey, current->left, range);
    // }
    // else if (current->key <= highkey) {
    //     range
    // }
}

void AVLTree::printPreorder(ostream& os, const AVLTreeNode* cur, int level) const {
    if (cur == NULL) {
        return;
    }
    else {
        printPreorder(os, cur->right, level+1);

        for (int i = 0; i < level; i++) {
            os << "\t";
        }
    }

    //print(os, cur);
    os << cur->key << ", " << cur->value << endl;

    printPreorder(os, cur->left, level+1);
}

// void AVLTree::print(ostream& os, const AVLTreeNode* cur) const {
//     os << cur->key << ", " << cur->value << endl;
// }