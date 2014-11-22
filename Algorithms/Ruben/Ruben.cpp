#include "Ruben.h"

Ruben::Ruben() {
    //LeeBase::LeeBase();
    kUsingRuben = true;
}

Ruben::Ruben(Maps *m) {
    //LeeBase::LeeBase();
    LeeBase::set_map(m);
    kUsingRuben = true;
}

Ruben::~Ruben() {
    //LeeBase::~LeeBase();
}

Ruben::Ruben(Maps *m, double korn) {
    //LeeBase::LeeBase();
    LeeBase::set_map(m);
    kKornModifier = korn;
    kUsingRuben = false;
}

void Ruben::start() {
    //LeeBase::start();
    printf("Starting Ruben's Algorithm\n");

    kWaveFrontPQ.push(kSource);

    solve_recursive(1);
}

int Ruben::solve_recursive(int iteration) {
// Base case 1: Not finding a solution
    //printf("size of queue: %lu\n", kWaveFront.size());
    if (kWaveFrontPQ.size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return iteration;
    }

    // Grab the first record
    Coordinates curr = kWaveFrontPQ.top();
    // pop off the first record
    kWaveFrontPQ.pop();

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
        kWaveFrontPQ.push(adjacent.at(x));
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

vector<Coordinates> Ruben::get_adjacent_coordinates(Coordinates c, int iteration) {
    vector<Coordinates> results;
    Coordinates temp;

    // (x, y+1)
    if (is_placeable(c.x, c.y + 1)) {
        temp.x = c.x;
        temp.y = c.y + 1;
        //if (!is_in_priority_queue(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x,y+1): (%d, %d)\n", temp.x, temp.y);
        //}
    }// else {printf("WE AREN'T PLACING: %d, %d ON THE QUEUE!!\n", c.x, c.y + 1);}
    // (x, y-1)
    if (is_placeable(c.x, c.y - 1)) {
        temp.x = c.x;
        temp.y = c.y - 1;
        //if (!is_in_priority_queue(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x,y-1): (%d, %d)\n", temp.x, temp.y);
        //}
    }// else {printf("WE AREN'T PLACING: %d, %d ON THE QUEUE!!\n", c.x, c.y - 1);}
    // (x+1, y)
    if (is_placeable(c.x + 1, c.y)) {
        temp.x = c.x + 1;
        temp.y = c.y;
        //if (!is_in_priority_queue(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
        //printf("Adding (x+1,y): (%d, %d)\n", temp.x, temp.y);
        //}
    }// else {printf("WE AREN'T PLACING: %d, %d ON THE QUEUE!!\n", c.x + 1, c.y);}
    // (x-1, y)
    if (is_placeable(c.x - 1, c.y)) {
        temp.x = c.x - 1;
        temp.y = c.y;
        //if (!is_in_priority_queue(temp)) {
            temp = calculate_metric(temp, iteration);
            results.push_back(temp);
            printf("Adding (x-1,y): (%d, %d)\n", temp.x, temp.y);
        //}
    }// else {printf("WE AREN'T PLACING: %d, %d ON THE QUEUE!!\n", c.x - 1, c.y);}
    return results;
}

Coordinates Ruben::calculate_metric(Coordinates c, int i) {
    if (kUsingRuben) {
        c.dist = calculate_lees_distance(c) + calculate_manhattan_distance(c, kSink);
    } else {
        c.dist = (int) ((calculate_lees_distance(c) + (kKornModifier * calculate_manhattan_distance(c, kSink))) * .5);
    }
    kMap->get_map()->at(c.x).at(c.y) = c.dist;
    return c;
}