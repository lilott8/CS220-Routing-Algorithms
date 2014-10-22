#include <vector>
#include <stdlib.h>
#include <string>
#include <ostream>
#include <iostream>
#include "Maps.h"
#include "../Coordinates.h"

using namespace std;

int difficulty;
bool initialized = false;
vector<vector <int> > map;

Coordinates source_coordinates;
Coordinates sink_coordinates;

Maps::Maps() {
    initialized = false;
}

Maps::Maps(int x) {
    difficulty = x;
    initialize_map();
    set_points();
    initialized = true;
}

vector< vector<int> > Maps::get_map() {
    return map;
}

void Maps::set_difficulty(int x) {
    difficulty = x;
    if (!initialized) {
        initialize_map();
        set_points();
    }
}

Coordinates Maps::get_sink_coordinates() {
    return sink_coordinates;
};

Coordinates Maps::get_source_coordinates() {
    return source_coordinates;
};

/**
* @method:
*   Init the map vector
*/
void Maps::initialize_map() {
    for(int x=0; x<difficulty; x++) {
        vector<int> v(difficulty,0);
        map.push_back(v);
    }
    set_points();
}

/**
* @method:
*   This sets the start and end points of our map
*/
void Maps::set_points() {
    srand(time(NULL));
    int startx = rand()%difficulty;
    int starty = rand()%difficulty;
    int endx = rand()%difficulty;
    int endy = rand()%difficulty;

    source_coordinates.x = startx;
    source_coordinates.y = starty;

    // ensure our start/ends aren't the same
    while(startx == endx && starty == endy) {
        endx = rand()%difficulty;
        endy = rand()%difficulty;
    }
    // Must occur after the loop so that
    // they are correct
    sink_coordinates.x = endx;
    sink_coordinates.y = endy;

    // set the values so our algorithm knows where
    // to start and end
    map.at(startx).at(starty) = -1;
    map.at(endx).at(endy) = -2;
}

void Maps::print_map() {
    string out = "";
    vector< vector<int> >::iterator row;
    vector<int>::iterator column;
    for(row = map.begin(); row != map.end(); row++) {
        for(column = row->begin(); column != row->end(); column++) {
            out += to_string(*column) + "\t";
        }
        out += "\n";
    }
    //printf("%s", out);
    cout << out << endl;
}

