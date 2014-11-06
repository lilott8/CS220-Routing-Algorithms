#pragma once

#include "../LeeBase/LeeBase.h"

class Lee3Bit : public LeeBase {
public:
    Lee3Bit();

    Lee3Bit(Maps *);

    ~Lee3Bit();

    void start();

private:
    int solve_recursive(int);

    vector<Coordinates> get_adjacent_coordinates(Coordinates);
};