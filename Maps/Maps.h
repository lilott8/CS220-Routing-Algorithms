#pragma once
#include <vector>
#include "../DataStructures/Global.h"

using namespace std;

class Maps {
public:
    // Constructor
    Maps();
    Maps(int);

    Maps(string);
    // Methods
    vector<vector<int> > *get_map();
    Maps &set_difficulty(int);
    Maps &set_source(int, int);
    Maps &set_sink(int, int);
    Coordinates get_source_coordinates();
    Coordinates get_sink_coordinates();
    void print_map();

    void zero_out_map();
    // Variables
    //static const typedef enum Labels {Empty, Blocked, L1, L2, L3} LabelType;
    static const int kSource = -1;
    static const int kSink = -2;
    static const int kUntraversable = -3;
    static const int kTraceback = -4;
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