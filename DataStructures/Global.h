#pragma once

/**
* @class
* There might be a time to
* extrapolate this into an entire
* class, right now it is just an
* easy way to move data between two classes
*/
struct Coordinates {
    int x;
    int y;
    int dist;
    int detour;
    int wave;
};

struct node {
    Coordinates coord;
    node *left;
    node *right;
    bool is_traversable;
};
