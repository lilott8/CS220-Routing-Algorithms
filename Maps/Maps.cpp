#include <vector>
#include <stdlib.h>
#include <string>
#include <ostream>
#include <iostream>
#include "Maps.h"

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

Maps::Maps(string fn) {

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

void Maps::zero_out_map() {
    int place = 0;
    for (int x = 0; x < map.size(); x++) {
        for (int y = 0; y < map.at(x).size(); y++) {
            place = map.at(x).at(y);
            if (place != Maps::kTraceback &&
                    place != Maps::kUntraversable &&
                    place != Maps::kSink &&
                    place != Maps::kSource) {
                map.at(x).at(y) = 0;
            }
        }
    }
}

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
    map.at(startx).at(starty) = Maps::kSource;
    map.at(endx).at(endy) = Maps::kSink;
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

