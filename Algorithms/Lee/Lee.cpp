#include <csignal>
#include <deque>
#include <iostream>
#include <math.h>
#include "../../Maps/Maps.h"
#include "Lee.h"
#include "../../DataStructures/BinaryTree.h"

using namespace std;

Maps *lee_map;

Coordinates sink_coords;
Coordinates source_coords;
BinaryTree bTree;

vector<Coordinates> trace_back;

int beginning_branches;

Lee::Lee(Maps* m) {
    lee_map = m;

    sink_coords = lee_map->get_sink_coordinates();
    source_coords = lee_map->get_source_coordinates();
}

Lee::~Lee() {}

void Lee::print_map() {
    string output = "";
    vector< vector<int> >::iterator row;
    vector<int>::iterator column;
    vector< vector<int> > *map = lee_map->get_map();
    for(row = map->begin(); row != map->end(); row++) {
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

void Lee::print_trace_back() {
    string output = "";
    for(Coordinates i : trace_back) {
        output += "(" + to_string(i.x) + ", "
                + to_string(i.y) + ")\t Distance: "
                + to_string(i.dist) + "\n";
    }
    char *a = new char[output.size()+1];
    memcpy(a,output.c_str(), output.size());
    printf("%s", a);
}

void Lee::start_lee() {
    deque<Coordinates> wave_front;

    Coordinates temp;

    int x = lee_map->get_source_coordinates().x;
    int y = lee_map->get_source_coordinates().y;

    temp.x = x;
    temp.y = y;
    temp.dist = 0;

    wave_front.push_back(temp);

    run_lee(&wave_front, 1);
    print_trace_back();
}

bool Lee::is_placeable(int x, int y) {
    if(lee_map->get_map()->at(x).at(y) == Maps::SOURCE_NUMBER) {
        return false;
    }
    if(lee_map->get_map()->at(x).at(y) == Maps::UNTRAVERSABLE_NUMBER) {
        return false;
    }
    if(lee_map->get_map()->at(x).at(y) > 0) {
        return false;
    }
    return true;
}

int Lee::calculate_distance(int x, int y) {
    // Source is always (x1, y1)
    int order1, order2, result;
    order1 = (source_coords.x - x)*(source_coords.x - x);
    order2 = (source_coords.y - y)*(source_coords.y - y);
    return (int) (sqrt(order1 + order2) + .5);
}


void Lee::run_lee(deque<Coordinates> *wave_front, int iteration) {
    printf("We are on iteration: %d\n", iteration);
    printf("Sink's coordinates are: (%d, %d)\n", sink_coords.x, sink_coords.y);

    // If we have nothing else to search, return
    printf("size of queue: %lu\n", wave_front->size());
    if(wave_front->size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return;
    }

    Coordinates curr = wave_front->front();
    wave_front->pop_front();
    Coordinates temp;

    // If we found our sink, let's leave!
    if(curr.x == sink_coords.x && curr.y == sink_coords.y) {
        printf("We found: (%d, %d) in %d moves\n",
                sink_coords.x, sink_coords.y, (int)floor(iteration/4)-1);
        printf("=====================\n\n");
        return;
    }

    int x = curr.x;
    int y = curr.y;
    int d = curr.dist;
    printf("***********\n");
    printf("Current coordinates: (%d, %d)\t Distance: %d\n", x, y, d);

    // (x, y+1)
    if((y+1) < lee_map->get_map()->at(x).size() && is_placeable(x, y+1)) {
        temp.x = x;
        temp.y = y+1;
        temp.dist = calculate_distance(temp.x, temp.y);
        lee_map->get_map()->at(x).at(y+1) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x,y+1): (%d, %d)\n", x, y+1);
    }
    // (x, y-1)
    if((y-1) >= 0 && is_placeable(x, y-1)) {
        temp.x = x;
        temp.y = y-1;
        temp.dist = calculate_distance(temp.x, temp.y);
        lee_map->get_map()->at(x).at(y-1) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x,y-1): (%d, %d)\n", x, y-1);
    }
    // (x+1, y)
    if((x+1) < lee_map->get_map()->size() && is_placeable(x+1, y)) {
        temp.x = x+1;
        temp.y = y;
        temp.dist = calculate_distance(temp.x, temp.y);
        lee_map->get_map()->at(x+1).at(y) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x+1,y): (%d, %d)\n", x+1, y);
    }
    // (x-1, y)
    if((x-1) >= 0 && is_placeable(x-1, y)) {
        temp.x = x-1;
        temp.y = y;
        temp.dist = calculate_distance(temp.x, temp.y);
        lee_map->get_map()->at(x-1).at(y) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x-1,y): (%d, %d)\n", x-1, y);
    }
    print_map();
    printf("=====================\n\n");
    return run_lee(wave_front, iteration+1);
}