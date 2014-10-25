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

void Lee::deprecated_start_lee() {

    deque<node*> queue;
    int nodes = 0;

    // holder for our coordinate struct
    Coordinates c;

    // This isn't the wave-front expansion that Lee's discusses
    // add all the elements greater than the source on the x-axis
    for(int x=source_coords.x; x<lee_map->get_map()->size();x++) {
        for(int y=source_coords.y;y<lee_map->get_map()->at(x).size();y++) {
            c.x = x;
            c.y = y;
            bTree.insert(c);
            nodes++;
        }
        // deduct 1 so that we don't add the same cells twice
        for(int y=source_coords.y-1;y>=0;y--) {
            c.x = x;
            c.y = y;
            bTree.insert(c);
            nodes++;
        }
    }

    // add all the elements less than the source on the x-axis
    for(int x=source_coords.x-1;x>=0;x--) {
        for(int y=source_coords.y;y<lee_map->get_map()->at(x).size();y++) {
            c.x = x;
            c.y = y;
            bTree.insert(c);
            nodes++;
        }
        // deduct 1 so that we don't add the same cells twice
        for(int y=source_coords.y-1;y>=0;y--) {
            c.x = x;
            c.y = y;
            bTree.insert(c);
            nodes++;
        }
    }

    printf("there are %d nodes, from counting in the loops\n", nodes);

    // Add the root of our tree, the source
    queue.push_back(bTree.get_root());
    // start the recursive breadth first search algorithm
    deprecated_run_lee(queue, 0);
}

/**
* Recursively called method for discovering the path
* to the sink from the source
* http://stackoverflow.com/questions/2969033/recursive-breadth-first-travel-function-in-java-or-c
*/
void Lee::deprecated_run_lee(deque<node*> queue, int iteration) {

    //printf("Size of queue at top of run_lee is: %lu\n", queue.size());
    // Base Case, nothing on our queue
    if(queue.size() == 0) {
        printf("Somehow we didn't find the sink at (%d, %d), with %d iterations.\n",
                sink_coords.y, sink_coords.x, iteration);
        return;
    }

    // Unfortunately this is how we have to do this
    // grab the first element from the queue
    node *curr_node = queue.front();
    // get the current set of coordinates
    Coordinates curr_coord = curr_node->coord;
    // save the distance!
    curr_coord.dist = iteration;
    // Check to see if our current point is optimally away from the source

    if(trace_back.size() == 0) {
        trace_back.push_back(curr_coord);
        printf("Added the initial spot (%d, %d) distance: %d\n",
                curr_coord.x, curr_coord.y, curr_coord.dist);
    } else if(curr_coord.dist <= trace_back.back().dist) {
        // Add the object to our vector
        //trace_back.push_back(&curr_coord);
        printf("We are adding point(%d, %d) to spot %d on trace back\n",
                curr_coord.x, curr_coord.y, iteration);
    } else {
        Coordinates temp = trace_back.back();
        printf("Current Coordinates: (%d, %d), %d \t Last Coord in trace_back: (%d, %d), %d\n",
                curr_coord.x, curr_coord.y, curr_coord.dist,temp.x, temp.y, temp.dist);
    }


    // then pop it off :(
    queue.pop_front();
    printf("We are looking at point(%d, %d)\n", curr_coord.x, curr_coord.y);

    // Case of finding our sink
    if(curr_coord.x == sink_coords.x && curr_coord.y == sink_coords.y) {
        printf("We found our sink (%d, %d) in %d moves.\n", sink_coords.x, sink_coords.y, iteration);
        return;
    }

    // breadth search here, we always add the left and right nodes
    // of the current node we are on!
    if(curr_node->left != NULL) {
        queue.push_back(curr_node->left);
        //printf("Size of queue after pushing a left leaf is: %lu\n", queue.size());
    }
    if(curr_node->right != NULL) {
        queue.push_back(curr_node->right);
        //printf("Size of queue after pushing a right leaf is: %lu\n", queue.size());
    }

    lee_map->get_map()->at(curr_coord.x).at(curr_coord.y) = iteration;
    printf("On iteration: %d\n", iteration);
    deprecated_run_lee(queue, iteration+1);
}

void Lee::start_lee() {
    deque<Coordinates> wave_front;
    //Coordinates *source = &lee_map->get_source_coordinates();

    Coordinates temp;

    int x = lee_map->get_source_coordinates().x;
    int y = lee_map->get_source_coordinates().y;

    temp.x = x;
    temp.y = y;
    temp.dist = 0;

    // segfault here :(
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


void Lee::run_lee(deque<Coordinates> *wave_front, int iteration) {
    printf("We are on iteration: %d\n", iteration);
    printf("Sink's coordinates are: (%d, %d)\n", sink_coords.x, sink_coords.y);
    // If we have nothing else to search, return
    printf("size of wavefront: %lu\n", wave_front->size());
    if(wave_front->size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return;
    }

    // Next segfault :(
    Coordinates curr = wave_front->front();
    wave_front->pop_front();
    Coordinates temp;

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
        temp.dist = iteration;
        lee_map->get_map()->at(x).at(y+1) = iteration;
        wave_front->push_back(temp);
        printf("Adding (x,y+1): (%d, %d)\n", x, y+1);
    }
    // (x, y-1)
    if((y-1) >= 0 && is_placeable(x, y-1)) {
        temp.x = x;
        temp.y = y-1;
        temp.dist = iteration;
        lee_map->get_map()->at(x).at(y-1) = iteration;
        wave_front->push_back(temp);
        printf("Adding (x,y-1): (%d, %d)\n", x, y-1);
    }
    // (x+1, y)
    if((x+1) < lee_map->get_map()->size() && is_placeable(x+1, y)) {
        temp.x = x+1;
        temp.y = y;
        temp.dist = iteration;
        lee_map->get_map()->at(x+1).at(y) = iteration;
        wave_front->push_back(temp);
        printf("Adding (x+1,y): (%d, %d)\n", x+1, y);
    }
    // (x-1, y)
    if((x-1) >= 0 && is_placeable(x-1, y)) {
        temp.x = x-1;
        temp.y = y;
        temp.dist = iteration;
        lee_map->get_map()->at(x-1).at(y) = iteration;
        wave_front->push_back(temp);
        printf("Adding (x-1,y): (%d, %d)\n", x-1, y);
    }
    print_map();
    printf("=====================\n\n");
    return run_lee(wave_front, iteration+1);
}