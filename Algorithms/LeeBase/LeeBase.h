#pragma once

#include <queue>
#include <deque>
#include "../../Maps/Maps.h"


class LeeBase {
public:
    LeeBase();

    LeeBase(Maps *);

    ~LeeBase();

    LeeBase &set_map(Maps *);

    LeeBase &set_coordinates(Coordinates, Coordinates);

    void start();

    // Make sure child classes can get access to these!
protected:
    Coordinates kSink;
    Coordinates kSource;
    Maps *kMap;
    deque<Coordinates> kWaveFront;
    vector<Coordinates> kTraceBack;

    int calculate_manhattan_distance(int, int);

    int calculate_manhattan_distance(Coordinates, Coordinates);

    int calculate_lees_distance(int);

    int caclulate_euclidean_distance(int, int);

    double calculate_euclidean_distance(Coordinates, Coordinates);

    bool is_sink(Coordinates);

    bool is_sink(int, int);

    bool is_source(Coordinates);

    bool is_source(int, int);

    bool is_adjacent(Coordinates, Coordinates);

    bool is_placeable(int x, int y);

    bool is_placeable(Coordinates);

    bool is_adjacent_to_source(Coordinates);

    bool is_in_vector(Coordinates);

    bool is_same_coordinate(Coordinates, Coordinates);
};