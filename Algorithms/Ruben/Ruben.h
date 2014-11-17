#pragma once

#include "../../Maps/Maps.h"
#include "../LeeBase/LeeBase.h"

class CompareCoordinatesRuben {
public:
    bool operator()(Coordinates &a, Coordinates &b) {
        // do the checking here!
        return a.dist >= b.dist;
    }
};

class Ruben : public LeeBase {
public:
    Ruben();

    Ruben(Maps *);

    // This is the korn implementation of Ruben!
    Ruben(Maps *, double);

    ~Ruben();

    void start();

private:
    bool kUsingRuben;

    double kKornModifier;

    priority_queue<Coordinates, vector<Coordinates>, CompareCoordinatesRuben> kWaveFrontPQ;

    int solve_recursive(int);

    vector<Coordinates> get_adjacent_coordinates(Coordinates, int);

    Coordinates calculate_metric(Coordinates, int);
};