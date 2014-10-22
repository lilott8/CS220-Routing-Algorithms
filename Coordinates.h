#pragma once

using namespace std;

/**
* @class
* There might be a time to
* extrapolate this into an entire
* class, right now it is just an
* easy way to move data between two classes
*/
class Coordinates {
public:
    // Constructors
    Coordinates();
    Coordinates(int, int);
    Coordinates(const Coordinates &c);
    Coordinates& operator= (const Coordinates &c);
    // Methods
    // Variables
    int x;
    int y;
private:
};