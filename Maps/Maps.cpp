#include <vector>
#include <stdlib.h>
#include <string>
#include <ostream>
#include <iostream>
#include <fstream>
#include "Maps.h"

using namespace std;

Maps::Maps() {
    kInitialized = false;
}

Maps::Maps(int x) {
    kDifficulty = x;
    initialize_map();
    set_points();
    kInitialized = true;
}

/**
* TODO: Figure out why I can't use my constants here!
*/
Maps::Maps(string fn) {
    ifstream inFile(fn);
    if (!inFile) {
        printf("Error finding file %s\n", fn.c_str());
    }
    string line;
    int line_number = 0;
    while (getline(inFile, line)) {

        vector<int> temp;
        kMap.push_back(temp);

        int i = 0;
        for (char &c : line) {
            if (c == '0') {
                kMap.at(line_number).push_back(0);
            } else if (c == 'b') {
                kMap.at(line_number).push_back(-3);
            } else if (c == 't') {
                kMap.at(line_number).push_back(-2);
                kSinkCoords.x = i;
                kSinkCoords.y = line_number;
            } else if (c == 's') {
                kMap.at(line_number).push_back(-1);
                kSourceCoords.x = i;
                kSourceCoords.y = line_number;
            }
            i++;
        }
        line_number++;
    }
    inFile.close();
    printf("Done reading file\n");
    printf("Source coords: %d, %d\n", kSourceCoords.x, kSourceCoords.y);
    printf("Sink coords: %d, %d\n", kSinkCoords.x, kSinkCoords.y);
}

vector< vector<int> > *Maps::get_map() {
    return &kMap;
}

Maps &Maps::set_difficulty(int x) {
    kDifficulty = x;
    if (!kInitialized) {
        initialize_map();
        kInitialized = true;
    }
    return *this;
}

Maps &Maps::set_sink(int x, int y) {
    kMap.at(x).at(y) = -2;
    kSinkCoords.x = x;
    kSinkCoords.y = y;
    return *this;
}

Maps &Maps::set_source(int x, int y) {
    kMap.at(x).at(y) = -1;
    kSourceCoords.x = x;
    kSourceCoords.y = y;
    return *this;
}

Coordinates Maps::get_sink_coordinates() {
    return kSinkCoords;
};

Coordinates Maps::get_source_coordinates() {
    return kSourceCoords;
};

void Maps::zero_out_map() {
    int place = 0;
    for (int x = 0; x < kMap.size(); x++) {
        for (int y = 0; y < kMap.at(x).size(); y++) {
            place = kMap.at(x).at(y);
            if (place != Maps::kTraceback &&
                    place != Maps::kUntraversable &&
                    place != Maps::kSink &&
                    place != Maps::kSource) {
                kMap.at(x).at(y) = 0;
            }
        }
    }
}

/**
* @method:
*   Init the map vector
*/
void Maps::initialize_map() {
    for (int x = 0; x < kDifficulty; x++) {
        vector<int> v(kDifficulty, 0);
        kMap.push_back(v);
    }
}

/**
* @method:
*   This sets the start and end points of our map
*/
void Maps::set_points() {
    srand(time(NULL));
    int startx = rand() % kDifficulty;
    int starty = rand() % kDifficulty;
    int endx = rand() % kDifficulty;
    int endy = rand() % kDifficulty;

    kSourceCoords.x = startx;
    kSourceCoords.y = starty;

    // ensure our start/ends aren't the same
    while(startx == endx && starty == endy) {
        endx = rand() % kDifficulty;
        endy = rand() % kDifficulty;
    }
    // Must occur after the loop so that
    // they are correct
    kSinkCoords.x = endx;
    kSinkCoords.y = endy;

    // set the values so our algorithm knows where
    // to start and end
    kMap.at(startx).at(starty) = Maps::kSource;
    kMap.at(endx).at(endy) = Maps::kSink;
}

void Maps::print_map() {
    string output = "";
    vector< vector<int> >::iterator row;
    vector<int>::iterator column;
    for (row = kMap.begin(); row != kMap.end(); row++) {
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

