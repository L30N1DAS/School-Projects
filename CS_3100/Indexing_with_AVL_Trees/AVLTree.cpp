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
    //check this
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
        current = new AVLTreeNode(key, value, getLeftHeight(), getRightHeight());
        numElts++;
        return true;
    }
    else if (key < current->key) {
        return insertHelper(key, value, current->left);
    }
    else if (key > current->key) {
        return insertHelper(key, value, current->right);
    }
    else {
        return false;
    }
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
        current->value = value;
        return true;
    }
}

int AVLTree::getHeight() {
    return getLeftHeight();
}

int AVLTree::getHeightHelper() {

}

int AVLTree::getLeftHeight() {
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

}

ostream& operator<<(ostream& os, const AVLTree& me) {
    int level = 0;
    me.printPreorder(os, me.root, level);
    return os;
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