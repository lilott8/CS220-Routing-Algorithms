#include <stddef.h>
#include "BinaryTree.h"

node *root;

BinaryTree::BinaryTree() {
    root = NULL;
}

BinaryTree::~BinaryTree() {}

void BinaryTree::destroy_tree(node *leaf) {
    if(leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void BinaryTree::insert(Coordinates c, node *leaf) {
    // It's less than so it goes left
    if(c.x < leaf->coord.x) {
        if(leaf->left != NULL) {
            insert(c, leaf->left);
        } else {
            leaf->left = new node;
            leaf->left->coord = c;
            leaf->left->left = NULL; // create NP's to new, non-existent nodes
            leaf->left->right = NULL; // create NP's to new, non-existent nodes
        }
        // if it's greater, go right!
    } else if(c.x > leaf->coord.x) {
        if (leaf->right != NULL) {
            insert(c, leaf->right);
        } else {
            leaf->right = new node;
            leaf->right->coord = c;
            leaf->right->left = NULL;
            leaf->right->right = NULL;
        }
        // If it's equal, then we will defer to the Y coordinate
    } else {
        // If it's less than the current y, then push it left
        if(c.y < leaf->coord.y) {
            if(leaf->left != NULL) {
                insert(c, leaf->left);
            } else {
                leaf->left = new node;
                leaf->left->coord = c;
                leaf->left->left = NULL; // create NP's to new, non-existent nodes
                leaf->left->right = NULL; // create NP's to new, non-existent nodes
            }
            // Otherwise, push it right
        } else {
            if (leaf->right != NULL) {
                insert(c, leaf->right);
            } else {
                leaf->right = new node;
                leaf->right->coord = c;
                leaf->right->left = NULL;
                leaf->right->right = NULL;
            }
        }
    }
}

node *BinaryTree::search(Coordinates c, node *leaf) {
    if(leaf != NULL) {
        // found the node we need
        if (c.x == leaf->coord.x && c.y == leaf->coord.y) {
            return leaf;
        }
        if (c.x < leaf->coord.x) {
            return search(c, leaf->left);
        } else {
            return search(c, leaf->right);
        }
    } else {
        return NULL;
    }
}

void BinaryTree::insert(Coordinates c) {
    if(root != NULL) {
        insert(c, root);
    } else {
        root = new node;
        root->coord = c;
        root->left = NULL;
        root->right = NULL;
    }
}

node *BinaryTree::search(Coordinates c) {
    return search(c, root);
}

void BinaryTree::destroy_tree() {
    destroy_tree(root);
}

node *BinaryTree::get_root() {
    return root;
}