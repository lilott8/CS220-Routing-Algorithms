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
    void deprecated_start_lee();
    void start_lee();
    void print_map();
    // Variables
private:
    // Methods
    void deprecated_run_lee(deque<node*>, int);
    void run_lee(deque<Coordinates> *, int);
    void print_trace_back();
    bool check_traversability(int, int);
    bool is_placeable(int, int);
    // Variables
    Maps *lee_map;
    Coordinates sink_coords;
    Coordinates source_coords;
};