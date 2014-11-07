#pragma once

#include "../../Maps/Maps.h"
#include "../LeeBase/LeeBase.h"

class Hadlock : public LeeBase {
public:
    Hadlock();

    Hadlock(Maps *);

    ~Hadlock();

    void start();

private:
    int solve_recursive(int);

    vector<Coordinates> get_adjacent_coordinates(Coordinates);

    bool is_closer_to_sink(Coordinates, Coordinates);
};