#include <vector>
#include <stdlib.h>
#include <string>
#include <ostream>
#include <iostream>
#include "Maps.h"
#include "../DataStructures/Global.h"

using namespace std;

/**int difficulty;
bool initialized = false;
vector<vector <int> > map;

Coordinates source_coordinates;
Coordinates sink_coordinates;**/

Maps::Maps() {
    initialized = false;
}

Maps::Maps(int x) {
    difficulty = x;
    initialize_map();
    set_points();
    initialized = true;
}

vector< vector<int> > *Maps::get_map() {
    return &map;
}

Maps &Maps::set_difficulty(int x) {
    difficulty = x;
    if (!initialized) {
        initialize_map();
        initialized = true;
    }
    return *this;
}

Maps &Maps::set_sink(int x, int y) {
    map.at(x).at(y) = -2;
    sink_coordinates.x = x;
    sink_coordinates.y = y;
    return *this;
}

Maps &Maps::set_source(int x, int y) {
    map.at(x).at(y) = -1;
    source_coordinates.x = x;
    source_coordinates.y = y;
    return *this;
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
    map.at(startx).at(starty) = SOURCE_NUMBER;
    map.at(endx).at(endy) = SINK_NUMBER;
}

void Maps::print_map() {
    string output = "";
    vector< vector<int> >::iterator row;
    vector<int>::iterator column;
    for(row = map.begin(); row != map.end(); row++) {
        for(column = row->begin(); column != row->end(); column++) {
            output += to_string(*column) + "\t";
        }
        output += "\n";
    }

    // http://www.cplusplus.com/forum/general/4422/
    char *a = new char[output.size()+1];
    a[output.size()] = 0;
    memcpy(a,output.c_str(), output.size());
    printf("%s", a);
    //cout << out << endl;
}

