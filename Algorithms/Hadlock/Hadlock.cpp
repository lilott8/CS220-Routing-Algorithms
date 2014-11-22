#include <deque>
#include <queue>
#include "Hadlock.h"

Hadlock::Hadlock() {
    //LeeBase::LeeBase();
}

Hadlock::Hadlock(Maps *m) {
    //LeeBase::LeeBase();
    LeeBase::set_map(m);
}

Hadlock::~Hadlock() {
    //LeeBase::~LeeBase();
}

void Hadlock::start() {
    //LeeBase::start();
    printf("Starting Hadlock's\n");

    kWaveFrontPQ.push(kSource);

    printf("Source coords: %d, %d\n", kSource.x, kSource.y);

    solve_recursive(0);
}

int Hadlock::solve_recursive(int iteration) {

    // Base case 1: Not finding a solution
    printf("size of queue: %lu\n", kWaveFrontPQ.size());
    if (kWaveFrontPQ.size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return iteration;
    }

    // Grab the first record
    Coordinates curr = kWaveFrontPQ.top();
    // pop off the first record
    kWaveFrontPQ.pop();

    // Base case 2: We found the sink
    if (is_sink(curr)) {
        // add the sink to the trace_back
        kTraceBack.push_back(curr);
        kMap->get_map()->at(curr.x).at(curr.y) = Maps::kTraceback;
        printf("We found the sink!\n");
        return iteration;
    }

    // Case 3: We still have places on the map to visit
    /**
    * Check each possibility of the next wavefront
    * TODO: Change the logic that calculates the cost
    */
    vector<Coordinates> adjacent = get_adjacent_coordinates(curr);

    for (int x = 0; x < adjacent.size(); x++) {
        kWaveFrontPQ.push(adjacent.at(x));
    }
    printf("******************************\n");
    kMap->print_map();
    solve_recursive(iteration + 1);

    // Handle the trace_back generation for the algorithm
    /**
    * TODO: Implement traceback logic for hadlock
    */
    if (kTraceBack.size() > 0 && curr.detour <= kTraceBack.back().detour
            && is_adjacent(curr, kTraceBack.back())) {
        kTraceBack.push_back(curr);
        kMap->get_map()->at(curr.x).at(curr.y) = Maps::kTraceback;
    }

    return iteration;
}

vector<Coordinates> Hadlock::get_adjacent_coordinates(Coordinates c) {
    vector<Coordinates> results;
    Coordinates temp;

    // We use this quite a bit, so we will save it
    double source_distance = calculate_euclidean_distance(c, kSink);

    // (x, y+1)
    if (is_placeable(c.x, c.y + 1)) {
        temp.x = c.x;
        temp.y = c.y + 1;
        if (!is_in_vector(temp)) {
            temp.dist = LeeBase::calculate_manhattan_distance(temp, kSource);
            if (calculate_euclidean_distance(temp, kSink) <=
                    source_distance) {
                printf("Temp: %d, %d dist: %d is closer to sink than our current!\n", temp.x, temp.y, temp.dist);
                temp.detour = c.detour;
            } else {
                printf("Temp is not closer to sink\n");
                temp.detour = c.detour + 1;
            }
            kMap->get_map()->at(temp.x).at(temp.y) = temp.detour;
            results.push_back(temp);
            printf("Adding (x,y+1): (%d, %d)\n", temp.x, temp.y);
        }
    }
    // (x, y-1)
    if (is_placeable(c.x, c.y - 1)) {
        temp.x = c.x;
        temp.y = c.y - 1;
        if (!is_in_vector(temp)) {
            temp.dist = calculate_manhattan_distance(temp, kSource);
            if (calculate_euclidean_distance(temp, kSink) <=
                    source_distance) {
                printf("Temp: %d, %d dist: %d is closer to sink than our current!\n", temp.x, temp.y, temp.dist);
                temp.detour = c.detour;
            } else {
                printf("Temp is not closer to sink\n");
                temp.detour = c.detour + 1;
            }
            kMap->get_map()->at(temp.x).at(temp.y) = temp.detour;
            results.push_back(temp);
            printf("Adding (x,y-1): (%d, %d)\n", temp.x, temp.y);
        }
    }
    // (x+1, y)
    if (is_placeable(c.x + 1, c.y)) {
        temp.x = c.x + 1;
        temp.y = c.y;
        if (!is_in_vector(temp)) {
            temp.dist = calculate_manhattan_distance(temp, kSource);
            if (calculate_euclidean_distance(temp, kSink) <=
                    source_distance) {
                printf("Temp: %d, %d dist: %d is closer to sink than our current!\n", temp.x, temp.y, temp.dist);
                temp.detour = c.detour;
            } else {
                printf("Temp is not closer to sink\n");
                temp.detour = c.detour + 1;
            }
            kMap->get_map()->at(temp.x).at(temp.y) = temp.detour;
            results.push_back(temp);
            printf("Adding (x+1,y): (%d, %d)\n", temp.x, temp.y);
        }
    }
    // (x-1, y)
    if (is_placeable(c.x - 1, c.y)) {
        temp.x = c.x - 1;
        temp.y = c.y;
        if (!is_in_vector(temp)) {
            temp.dist = calculate_manhattan_distance(temp, kSource);
            if (calculate_euclidean_distance(temp, kSink) <=
                    source_distance) {
                printf("Temp: %d, %d dist: %d is closer to sink than our current!\n", temp.x, temp.y, temp.dist);
                temp.detour = c.detour;
            } else {
                printf("Temp is not closer to sink\n");
                temp.detour = c.detour + 1;
            }
            kMap->get_map()->at(temp.x).at(temp.y) = temp.detour;
            results.push_back(temp);
            printf("Adding (x-1,y): (%d, %d)\n", temp.x, temp.y);
        }
    }
    return results;
}


bool Hadlock::is_in_vector(Coordinates c) {
    return false;
}