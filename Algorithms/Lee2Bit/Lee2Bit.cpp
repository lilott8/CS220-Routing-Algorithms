#include <deque>
#include "Lee2Bit.h"

Lee2Bit::Lee2Bit() {
    LeeBase::LeeBase();
}

Lee2Bit::Lee2Bit(Maps *m) {
    LeeBase::LeeBase();
    LeeBase::set_map(m);
}

Lee2Bit::~Lee2Bit() {
    LeeBase::~LeeBase();
}

void Lee2Bit::start() {
    LeeBase::start();

    LeeBase::kWaveFront.push_back(kSource);

    solve_recursive(0);
}

int Lee2Bit::solve_recursive(int iteration) {

    iteration = iteration == 4 ? 0 : iteration;

    // Base case 1: Not finding a solution
    printf("size of queue: %lu\n", kWaveFront.size());
    if (kWaveFront.size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return iteration;
    }

    // Grab the first record
    Coordinates curr = kWaveFront.front();
    // pop off the first record
    kWaveFront.pop_front();

    // Base case 2: We found the sink
    if (is_sink(curr)) {
        // add the sink to the trace_back
        kTraceBack.push_back(curr);
        kMap->get_map()->at(curr.x).at(curr.y) = Maps::kTraceback;
        return iteration;
    }

    // Case 3: We still have places on the map to visit
    /**
    * Check each possibility of the next wavefront
    */
    vector<Coordinates> adjacent = get_adjacent_coordinates(curr, iteration);

    for (int x = 0; x < adjacent.size(); x++) {
        kWaveFront.push_back(adjacent.at(x));
    }

    solve_recursive(iteration + 1);

    // Handle the trace_back generation for the algorithm
    /**
    * TODO: Add the logic for the trace back here
    */

    /**
    * END
    */

    return iteration;
}

vector<Coordinates> Lee2Bit::get_adjacent_coordinates(Coordinates c, int iteration) {
    vector<Coordinates> results;
    Coordinates temp;

    // (x, y+1)
    if (is_placeable(c.x, c.y + 1)) {
        temp.x = c.x;
        temp.y = c.y + 1;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x,y+1): (%d, %d)\n", temp.x, temp.y);
        }
    }
    // (x, y-1)
    if (is_placeable(c.x, c.y - 1)) {
        temp.x = c.x;
        temp.y = c.y - 1;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x,y-1): (%d, %d)\n", temp.x, temp.y);
        }
    }
    // (x+1, y)
    if (is_placeable(c.x + 1, c.y)) {
        temp.x = c.x + 1;
        temp.y = c.y;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x+1,y): (%d, %d)\n", temp.x, temp.y);
        }
    }
    // (x-1, y)
    if (is_placeable(c.x - 1, c.y)) {
        temp.x = c.x - 1;
        temp.y = c.y;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x-1,y): (%d, %d)\n", temp.x, temp.y);
        }
    }
    return results;
}

/**
* TODO: Implement 2-bit encoding logic here
*/
Coordinates Lee2Bit::calculate_metric(Coordinates a, int iteration) {
    Coordinates temp = a;

    temp.dist = iteration;

    kMap->get_map()->at(temp.x).at(temp.y) = temp.dist;

    return temp;
}