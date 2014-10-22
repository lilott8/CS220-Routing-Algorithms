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
    Lee(Maps);
    ~Lee();
    // Methods
    void start_lee();
    // Variables
private:
    // Methods
    void run_lee(deque<node>, int*);
    // Variables
    Maps lee_map;
    Coordinates sink_coords;
    Coordinates source_coords;
    bool check_traversability(int, int);
};