#pragma once
#include <vector>
#include "../DataStructures/Global.h"

using namespace std;

class Maps {
public:
    // Constructor
    Maps();
    Maps(int);
    // Methods
    vector<vector<int> > get_map();
    void set_difficulty(int);
    void print_map();
    Coordinates get_source_coordinates();
    Coordinates get_sink_coordinates();
    // Variables
    static const int SOURCE_NUMBER = -1;
    static const int SINK_NUMBER = -2;
    static const int UNTRAVERSABLE_NUMBER = -3;
private:
    // Methods
    void initialize_map();
    void set_points();
    // Variables
    vector<vector<int> > map;
    int difficulty;
    bool initialized;
    Coordinates source_coordinates;
    Coordinates sink_coordinates;
};