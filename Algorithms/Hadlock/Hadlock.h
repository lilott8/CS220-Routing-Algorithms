#pragma once

#include "../../Maps/Maps.h"
#include "../LeeBase/LeeBase.h"

class CompareCoordinatesHadlock {
public:
    bool operator()(Coordinates &a, Coordinates &b) {
        // do the checking here!
        return a.detour >= b.detour;
    }
};

class Hadlock : public LeeBase {
public:
    Hadlock();

    Hadlock(Maps *);

    ~Hadlock();

    void start();

private:
    priority_queue<Coordinates, vector<Coordinates>, CompareCoordinatesHadlock> kWaveFrontPQ;

    int solve_recursive(int);

    vector<Coordinates> get_adjacent_coordinates(Coordinates);

    bool is_in_vector(Coordinates);

    Coordinates calculate_metric(Coordinates, Coordinates);
};