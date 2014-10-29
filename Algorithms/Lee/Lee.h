#pragma once
#include <deque>
#include "../../Maps/Maps.h"
#include "../../DataStructures/Global.h"

using namespace std;

class Coordinates;
class Maps;

class Lee {

public:
    // Constructor
    Lee(Maps*);
    ~Lee();
    // Methods
    void start_lee();
    void print_map();
    // Variables
private:
    // Methods
    void run_lee(deque<Coordinates> *, vector<Coordinates> *, int);
    void print_trace_back(vector<Coordinates>);
    bool check_traversability(int, int);
    bool is_placeable(int, int);
    bool is_adjacent(Coordinates, Coordinates);
    int calculate_euclidean_distance(int, int);
    int calculate_manhattan_distance(int, int);
    int calculate_manhattan_distance(Coordinates, Coordinates);
    // Variables
    Maps *lee_map;
    Coordinates sink_coords;
    Coordinates source_coords;
};