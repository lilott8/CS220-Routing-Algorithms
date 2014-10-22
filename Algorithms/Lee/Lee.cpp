#include <csignal>
#include <deque>
#include "../../Maps/Maps.h"
#include "Lee.h"
#include "../../Coordinates.h"

using namespace std;

int lee_value;
Maps lee_map;

Coordinates sink_coords{};
Coordinates source_coords{};

Lee::Lee(Maps m) {
    lee_map = m;
    sink_coords = lee_map.get_sink_coordinates();
    source_coords = lee_map.get_source_coordinates();
}

void Lee::start_lee() {

    deque<Coordinates> queue;

    // add the first row!
    for(int x = source_coords.x;x<lee_map.get_map().size();x++) {
        queue.push_back(Coordinates(x, source_coords.y));
    }
    for(int x = source_coords.x;x>=0;x--) {
        queue.push_back(Coordinates(x,source_coords.y));
    }
    run_lee(queue, 0);

}

/**
* Recursively called method for discovering the path
* to the sink from the source
*/
void Lee::run_lee(deque<Coordinates> queue, int iteration) {
    // Base Case
    if(queue.size() == 0) {
        return;
    }

    // add the breadth addition here

    // recurse
    run_lee(queue, iteration++);


}