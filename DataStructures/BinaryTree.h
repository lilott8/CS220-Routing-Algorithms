#include "../DataStructures/Global.h"

#pragma once

class BinaryTree {

public:
    BinaryTree();
    ~BinaryTree();

    void insert(Coordinates c);
    node *search(Coordinates c);
    void destroy_tree();
    node &get_root();

private:
    void destroy_tree(node *leaf);
    void insert(Coordinates c, node *left);
    node *search(Coordinates coord, node *leaf);

    node *root;
};