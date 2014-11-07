#pragma once

#include "../../Maps/Maps.h"
#include "../LeeBase/LeeBase.h"

class Ruben : public LeeBase {
public:
    Ruben();

    Ruben(Maps *);

    ~Ruben();

    void start();

private:
    int solve_recursive(int);

    vector<Coordinates> get_adjacent_coordinates(Coordinates);

    bool is_in_vector(Coordinates);
};