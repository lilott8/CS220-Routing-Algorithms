#include <tkDecls.h>
#include "Coordinates.h"

int x;
int y;
Coordinates coordinate;

Coordinates::Coordinates(int a, int b){
    x = a;
    y = b;
}

Coordinates::Coordinates(const Coordinates &source) {
    coordinates = source.coordinates;
}

Coordinates& Coordinates::operator= (const Coordinates &source) {
    this->x = source.x;
    this->y = source.y;

    return *this;
}