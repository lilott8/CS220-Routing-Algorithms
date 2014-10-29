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

void Lee::print_trace_back(vector<Coordinates> trace_back) {
    string output = "";
    int x = 0;
    for(Coordinates i : trace_back) {
        output += "Record " + to_string(x)
                + ": (" + to_string(i.x) + ", "
                + to_string(i.y) + ")\t Distance: "
                + to_string(i.dist) + "\n";
        x++;
    }
    char *a = new char[output.size()+1];
    memcpy(a,output.c_str(), output.size());
    printf("+++++++++++++++++++++\n%s\n+++++++++++++++++++++\n", a);
}

void Lee::start_lee() {
    deque<Coordinates> wave_front;
    vector<Coordinates> trace_back;

    Coordinates temp;

    int x = lee_map->get_source_coordinates().x;
    int y = lee_map->get_source_coordinates().y;

    temp.x = x;
    temp.y = y;
    temp.dist = 0;

    wave_front.push_back(temp);

    run_lee(&wave_front, &trace_back, 0);

    // this is sort of cheating...
    lee_map->get_map()->at(sink_coords.x).at(sink_coords.y) = Maps::TRACE_BACK_NUMBER;

    print_trace_back(trace_back);
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

int Lee::calculate_euclidean_distance(int x, int y) {
    // Source is always (x1, y1)
    int order1, order2;
    order1 = (source_coords.x - x)*(source_coords.x - x);
    order2 = (source_coords.y - y)*(source_coords.y - y);
    // http://stackoverflow.com/questions/9695329/c-how-to-round-a-double-to-an-int
    return (int) (sqrt(order1 + order2) + .5);
}

int Lee::calculate_manhattan_distance(int x, int y) {
    int order1, order2;
    order1 = abs(x - source_coords.x);
    order2 = abs(y - source_coords.y);
    return order1 + order2;
}

int Lee::calculate_manhattan_distance(Coordinates curr, Coordinates prev) {
    int order1, order2;
    order1 = abs(curr.x - prev.x);
    order2 = abs(curr.y - prev.y);
    return order1 + order2;
}


void Lee::run_lee(deque<Coordinates> *wave_front, vector<Coordinates> *trace_back, int iteration) {
    printf("We are on iteration: %d\n", iteration);
    printf("Sink's coordinates are: (%d, %d)\n", sink_coords.x, sink_coords.y);

    // Base case 1: Not finding a solution
    printf("size of queue: %lu\n", wave_front->size());
    if(wave_front->size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return;
    }

    // Grab the first record
    Coordinates curr = wave_front->front();
    // pop off the first record
    wave_front->pop_front();
    // create a single holder var for our new coordinates
    Coordinates temp;

    // Base case 2: We found the sink
    if(curr.x == sink_coords.x && curr.y == sink_coords.y) {
        printf("We found: (%d, %d) in %d moves\n",
                sink_coords.x, sink_coords.y, (int)floor(iteration/4)-1);
        printf("=====================\n\n");
        // add the sink to the trace_back
        trace_back->push_back(curr);
        return;
    }

    // Case 3: We still have places on the map to visit
    // This is just for ease of typing
    int x = curr.x;
    int y = curr.y;
    int d = curr.dist;

    printf("*********************\n");
    printf("Current coordinates: (%d, %d)\t Distance: %d\n", x, y, d);

    /**
    * Check each possibility of the next wavefront
    */
    // (x, y+1)
    if ((y + 1) < lee_map->get_map()->at(x).size() && is_placeable(x, y + 1)) {
        temp.x = x;
        temp.y = y + 1;
        temp.dist = calculate_manhattan_distance(temp.x, temp.y);
        //temp.dist = calculate_euclidean_distance(temp.x, temp.y);
        //temp.dist = iteration;
        lee_map->get_map()->at(x).at(y + 1) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x,y+1): (%d, %d)\n", x, y + 1);
    }
    // (x, y-1)
    if ((y - 1) >= 0 && is_placeable(x, y - 1)) {
        temp.x = x;
        temp.y = y - 1;
        temp.dist = calculate_manhattan_distance(temp.x, temp.y);
        //temp.dist = calculate_euclidean_distance(temp.x, temp.y);
        //temp.dist = iteration;
        lee_map->get_map()->at(x).at(y - 1) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x,y-1): (%d, %d)\n", x, y - 1);
    }
    // (x+1, y)
    if ((x + 1) < lee_map->get_map()->size() && is_placeable(x + 1, y)) {
        temp.x = x + 1;
        temp.y = y;
        temp.dist = calculate_manhattan_distance(temp.x, temp.y);
        //temp.dist = calculate_euclidean_distance(temp.x, temp.y);
        //temp.dist = iteration;
        lee_map->get_map()->at(x + 1).at(y) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x+1,y): (%d, %d)\n", x + 1, y);
    }
    // (x-1, y)
    if ((x - 1) >= 0 && is_placeable(x - 1, y)) {
        temp.x = x - 1;
        temp.y = y;
        temp.dist = calculate_manhattan_distance(temp.x, temp.y);
        //temp.dist = calculate_euclidean_distance(temp.x, temp.y);
        //temp.dist = iteration;
        lee_map->get_map()->at(x - 1).at(y) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x-1,y): (%d, %d)\n", x - 1, y);
    }
    print_map();
    printf("=====================\n\n");

    run_lee(wave_front, trace_back, iteration+1);

    // This is the last "portion" that needs to be fixed.
    // note: check to see if it is completely adjacent, not
    // just within one of distance.
    if(trace_back->size() > 0 && curr.dist <= trace_back->back().dist
            && is_adjacent(curr, trace_back->back())) {
        trace_back->push_back(curr);
        lee_map->get_map()->at(curr.x).at(curr.y) = Maps::TRACE_BACK_NUMBER;
    }
}

bool Lee::is_adjacent(Coordinates curr, Coordinates prev) {
    // If it's the source, add it!
    if(curr.dist == 0) {
        return true;
    }
    int euclidean_x, euclidean_y, delta_x, delta_y;
    double result;
    euclidean_x = (curr.x - prev.x)*(curr.x - prev.x);
    euclidean_y = (curr.y - prev.y)*(curr.y - prev.y);
    // By using euclidean distance we can jump diagonally...
    // which isn't ok.
    result = sqrt(euclidean_x + euclidean_y);
    result = calculate_manhattan_distance(curr, prev);

    printf("is Current(%d, %d) close to Previous(%d, %d), it is: %f away\n",
            curr.x, curr.y, prev.x, prev.y, result);
    // Calculate the deltas between x and y,
    // this will prevent the diagonal jumping
    delta_x = abs(curr.x - prev.x);
    delta_y = abs(curr.y - prev.y);
    // Just for debugging!
    if((delta_x == 0 && delta_y == 1) || (delta_x == 1 && delta_y == 0)) {
        printf("Delta_x: %d, Delta_y: %d\n", delta_x, delta_y);
    } else {
        printf("it's greater than one!\n");
    }
    printf("---------------------\n");
    // make sure the result is 1 or less and the delta on x or y is 1
    return result <= 1.0 && (delta_x == 1 || delta_y == 1);
}