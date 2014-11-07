#include <deque>
#include "LeeOriginal.h"

LeeOriginal::LeeOriginal() {
    LeeBase::LeeBase();
}

LeeOriginal::LeeOriginal(Maps *m) {
    LeeBase::LeeBase();
    LeeBase::set_map(m);
}

LeeOriginal::~LeeOriginal() {
    LeeBase::~LeeBase();
}

void LeeOriginal::start() {
    LeeBase::start();

    LeeBase::kWaveFront.push_back(kSource);

    solve_recursive(0);
}

int LeeOriginal::solve_recursive(int iteration) {

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
    if (kTraceBack.size() > 0 && curr.dist <= kTraceBack.back().dist
            && is_adjacent(curr, kTraceBack.back())) {
        kTraceBack.push_back(curr);
        kMap->get_map()->at(curr.x).at(curr.y) = Maps::kTraceback;
    }
    return iteration;
}

vector<Coordinates> LeeOriginal::get_adjacent_coordinates(Coordinates c, int iteration) {
    vector<Coordinates> results;
    Coordinates temp;

    // (x, y+1)
    if (is_placeable(c.x, c.y + 1)) {
        temp.x = c.x;
        temp.y = c.y + 1;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp);
            results.push_back(temp);
            printf("Adding (x,y+1): (%d, %d)\n", temp.x, temp.y);
        }
    }
    // (x, y-1)
    if (is_placeable(c.x, c.y - 1)) {
        temp.x = c.x;
        temp.y = c.y - 1;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp);
            results.push_back(temp);
            printf("Adding (x,y-1): (%d, %d)\n", temp.x, temp.y);
        }
    }
    // (x+1, y)
    if (is_placeable(c.x + 1, c.y)) {
        temp.x = c.x + 1;
        temp.y = c.y;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp);
            results.push_back(temp);
            printf("Adding (x+1,y): (%d, %d)\n", temp.x, temp.y);
        }
    }
    // (x-1, y)
    if (is_placeable(c.x - 1, c.y)) {
        temp.x = c.x - 1;
        temp.y = c.y;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp);
            results.push_back(temp);
            printf("Adding (x-1,y): (%d, %d)\n", temp.x, temp.y);
        }
    }
    return results;
}

Coordinates LeeOriginal::calculate_metric(Coordinates a) {
    Coordinates temp = a;

    temp.dist = LeeBase::calculate_manhattan_distance(a, kSource);

    kMap->get_map()->at(temp.x).at(temp.y) = temp.dist;

    return temp;
}