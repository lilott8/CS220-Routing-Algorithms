#include <deque>
#include "LeeOriginal.h"

LeeOriginal::LeeOriginal() {
    //LeeBase::LeeBase();
}

LeeOriginal::LeeOriginal(Maps *m) {
    //LeeBase::LeeBase();
    LeeBase::set_map(m);
}

LeeOriginal::~LeeOriginal() {
    // TODO: Figure out why this line sigabrts
    // LeeBase::~LeeBase();
}

void LeeOriginal::start() {
    LeeBase::start();
    printf("Starting LeeOriginal\n");

    LeeBase::kWaveFront.push_back(kMap->get_source_coordinates());

    solve_recursive(1);
}

int LeeOriginal::solve_recursive(int iteration) {

    printf("Queue size: %d\n", kWaveFront.size());

    // Base case 1: Not finding a solution
    //printf("size of queue: %lu\n", kWaveFront.size());
    if (kWaveFront.size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return iteration;
    }

    // Grab the first record
    Coordinates curr = kWaveFront.front();
    // pop off the first record
    kWaveFront.pop_front();

    printf("Curr Coordinates: %d, %d\n", curr.x, curr.y);

    // Base case 2: We found the sink
    if (is_sink(curr) || kMap->get_map()->at(curr.x).at(curr.y) == Maps::kSink) {
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
    printf("=========================\n");
    kMap->print_map();
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
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x,y+1): (%d, %d)\n", temp.x, temp.y);
        }
    }// else {printf("WE AREN'T PLACING: %d, %d ON THE QUEUE!!\n", c.x, c.y + 1);}
    // (x, y-1)
    if (is_placeable(c.x, c.y - 1)) {
        temp.x = c.x;
        temp.y = c.y - 1;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x,y-1): (%d, %d)\n", temp.x, temp.y);
        }
    }// else {printf("WE AREN'T PLACING: %d, %d ON THE QUEUE!!\n", c.x, c.y - 1);}
    // (x+1, y)
    if (is_placeable(c.x + 1, c.y)) {
        temp.x = c.x + 1;
        temp.y = c.y;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x+1,y): (%d, %d)\n", temp.x, temp.y);
        }
    }// else {printf("WE AREN'T PLACING: %d, %d ON THE QUEUE!!\n", c.x + 1, c.y);}
    // (x-1, y)
    if (is_placeable(c.x - 1, c.y)) {
        temp.x = c.x - 1;
        temp.y = c.y;
        if (!is_in_vector(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x-1,y): (%d, %d)\n", temp.x, temp.y);
        }
    }// else {printf("WE AREN'T PLACING: %d, %d ON THE QUEUE!!\n", c.x - 1, c.y);}
    return results;
}

Coordinates LeeOriginal::calculate_metric(Coordinates a, int i) {
    Coordinates temp = a;

    //temp.dist = LeeBase::calculate_manhattan_distance(a, kSource);
    temp.dist = LeeBase::calculate_lees_distance(a);

    kMap->get_map()->at(temp.x).at(temp.y) = temp.dist;

    return temp;
}