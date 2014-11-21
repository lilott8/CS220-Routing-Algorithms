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
Coordinates Lee2Bit::calculate_metric(Coordinates c, int iteration) {
    Coordinates temp = c;

    // take care of our seed case
    vector<int> answer;
    answer.push_back(0);
    answer.push_back(0);
    answer.push_back(0);
    answer.push_back(0);
    //vector<int> answer;
    // (x, y+1) EAST answer[1]
    if (is_in_bounds(c.x, c.y + 1) && is_in_bounds(c.x, c.y + 2)) {
        answer.at(1) = kMap->get_map()->at(c.x).at(c.y + 1) +
                kMap->get_map()->at(c.x).at(c.y + 2);
    }
    // (x, y-1) WEST answer[3]
    if (is_in_bounds(c.x, c.y - 1) && is_in_bounds(c.x, c.y - 2)) {
        answer.at(3) = kMap->get_map()->at(c.x).at(c.y - 1) +
                kMap->get_map()->at(c.x).at(c.y - 2);
    }
    // (x+1, y) NORTH answer[0]
    if (is_in_bounds(c.x + 1, c.y && is_in_bounds(c.x + 2, c.y))) {
        answer.at(0) = kMap->get_map()->at(c.x + 1).at(c.y) +
                kMap->get_map()->at(c.x + 2).at(c.y);
    }
    // (x-1, y) SOUTH answer[2]
    if (is_in_bounds(c.x - 1, c.y) && is_in_bounds(c.x - 2, c.y)) {
        answer.at(2) = kMap->get_map()->at(c.x - 1).at(c.y) +
                kMap->get_map()->at(c.x - 2).at(c.y);
    }
    printf("Our options are:\n");
    int new_low = 0;
    for (int x = 0; x < answer.size(); x++) {
        if (answer.at(x) >= 1 && answer.at(x) > new_low) {
            printf("Changing new_low from: %d to %d\n", new_low, answer.at(x));
            new_low = answer.at(x);
        }
        printf("%d: %d\n", x, answer.at(x));
    }
    printf("Done with options\n");

    kMap->get_map()->at(temp.x).at(temp.y) = temp.dist + 1;

    return temp;
}