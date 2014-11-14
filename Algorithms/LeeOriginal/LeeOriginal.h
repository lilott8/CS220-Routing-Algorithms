#pragma once

#include "../LeeBase/LeeBase.h"

class LeeOriginal : public LeeBase {
public:
    LeeOriginal();

    LeeOriginal(Maps *);

    ~LeeOriginal();

    void start();

private:
    int solve_recursive(int);

    vector<Coordinates> get_adjacent_coordinates(Coordinates, int);

    Coordinates calculate_metric(Coordinates, int);
};