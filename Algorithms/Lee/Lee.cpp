#include <csignal>
#include <deque>
#include <iostream>
#include "../../Maps/Maps.h"
#include "Lee.h"
#include "../../DataStructures/BinaryTree.h"

using namespace std;

Maps *lee_map;

Coordinates sink_coords;
Coordinates source_coords;
BinaryTree bTree;

int iteration;

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
    vector< vector<int> > map = lee_map->get_map();
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

void Lee::start_lee() {

    deque<node*> queue;
    int nodes = 0;

    // holder for our coordinate struct
    Coordinates c;

    // add all the elements greater than the source on the x-axis
    for(int x=source_coords.x; x<lee_map->get_map().size();x++) {
        for(int y=source_coords.y;y<lee_map->get_map().at(x).size();y++) {
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
        for(int y=source_coords.y;y<lee_map->get_map().at(x).size();y++) {
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

    queue.push_back(bTree.get_root());
    run_lee(queue, 0);
}

/**
* Recursively called method for discovering the path
* to the sink from the source
* http://stackoverflow.com/questions/2969033/recursive-breadth-first-travel-function-in-java-or-c
*/
void Lee::run_lee(deque<node*> queue, int iteration) {

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
    Coordinates curr_coord = curr_node->coord;
    // then pop it off :(
    queue.pop_front();
    printf("We are looking at point(%d, %d)\n", curr_coord.x, curr_coord.y);

    // Case of finding our sink
    if(curr_coord.x == sink_coords.x && curr_coord.y == sink_coords.y) {
        printf("We found our sink (%d, %d) in %d moves.\n", sink_coords.x, sink_coords.y, iteration);
        return;
    }

    // breadth search here
    if(curr_node->left != NULL) {
        queue.push_back(curr_node->left);
        //printf("Size of queue after pushing a left leaf is: %lu\n", queue.size());
    }
    if(curr_node->right != NULL) {
        queue.push_back(curr_node->right);
        //printf("Size of queue after pushing a right leaf is: %lu\n", queue.size());
    }

    //printf("Size of queue at end of method: %lu\n", queue.size());
    lee_map->get_map().at(curr_coord.x).at(curr_coord.y) = iteration;
    printf("On iteration: %d\n", iteration);
    run_lee(queue, iteration+1);
}