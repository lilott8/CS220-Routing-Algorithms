#pragma once

#include "../LeeBase/LeeBase.h"

class Lee2Bit : public LeeBase {
public:
    Lee2Bit();

    Lee2Bit(Maps *);

    ~Lee2Bit();

    void start();

private:
    int solve_recursive(int);

    vector<Coordinates> get_adjacent_coordinates(Coordinates);
};