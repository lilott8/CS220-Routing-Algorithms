#pragma once

using namespace std;

/**
* @class
* There might be a time to
* extrapolate this into an entire
* class, right now it is just an
* easy way to move data between two classes
*/
extern struct Coordinates {
    int x;
    int y;
};

extern struct node {
    Coordinates coord;
    node *left;
    node *right;
    bool is_traversable;
};