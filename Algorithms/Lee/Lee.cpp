#include <csignal>
#include <deque>
#include <iostream>
#include "../../Maps/Maps.h"
//#include "../../DataStructures/Coordinates.h"
#include "Lee.h"
#include "../../DataStructures/BinaryTree.h"

using namespace std;

Maps lee_map;

Coordinates sink_coords;
Coordinates source_coords;
Coordinates temp;
BinaryTree bTree;

Lee::Lee(Maps m) {
    lee_map = m;

    sink_coords = lee_map.get_sink_coordinates();
    source_coords = lee_map.get_source_coordinates();
}

Lee::~Lee() {
    /*
    delete bTree;
    delete temp;
    delete source_coords;
    delete sink_coords;
    delete lee_map;
     */
}

void Lee::start_lee() {

    deque<node> queue;

    // holder for our coordinate struct
    Coordinates c;

    // add all the elements greater than the sink on the x-axis
    for(int x=source_coords.x; x<lee_map.get_map().size();x++) {
        for(int y=source_coords.y;y<lee_map.get_map().at(x).size();y++) {
            c.x = x;
            c.y = y;
            bTree.insert(c);
        }
        // deduct 1 so that we don't add the same cells twice
        for(int y=source_coords.y-1;y>=0;y--) {
            c.x = x;
            c.y = y;
            bTree.insert(c);
        }
    }

    // add all the elements less than the sink on the x-axis
    for(int x=source_coords.x;x>=0;x--) {
        for(int y=source_coords.y;y<lee_map.get_map().at(x).size();y++) {
            c.x = x;
            c.y = y;
            bTree.insert(c);
        }
        // deduct 1 so that we don't add the same cells twice
        for(int y=source_coords.y-1;y>=0;y--) {
            c.x = x;
            c.y = y;
            bTree.insert(c);
        }
    }
    queue.push_back(bTree.get_root());
    run_lee(queue, 0);
}

/**
* Recursively called method for discovering the path
* to the sink from the source
* http://stackoverflow.com/questions/2969033/recursive-breadth-first-travel-function-in-java-or-c
*/
void Lee::run_lee(deque<node> queue, int *iteration) {

    printf("Size of queue is: %d\n", queue.size());
    // Base Case, nothing on our queue
    if(queue.size() == 0) {
        printf("Somehow we didn't find the sink at (%d, %d), with %d iterations.\n",
        sink_coords.y, sink_coords.x, iteration);
        return;
    }

    // Unfortunately this is how we have to do this
    // grab the first element from the queue
    node curr_node = queue.front();
    Coordinates curr_coord = curr_node.coord;
    // then pop it off :(
    queue.pop_front();
    printf("Size of queue is: %d\n", queue.size());

    // Case of finding our sink
    if(curr_coord.x == sink_coords.x && curr_coord.y == sink_coords.y) {
        printf("We found our sink in %d moves.\n", iteration);
        return;
    }

    // breadth search here
    if(curr_node.left != NULL) {
        queue.push_back((node &)curr_node.left);
        printf("Size of queue is: %d\n", queue.size());
    }
    if(curr_node.right != NULL) {
        queue.push_back((node &)curr_node.right);
        printf("Size of queue is: %d\n", queue.size());
    }

    run_lee(queue, iteration++);
}