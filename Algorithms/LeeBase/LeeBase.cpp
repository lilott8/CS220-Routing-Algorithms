#include <deque>
#include <stdlib.h>
#include "LeeBase.h"

Maps *kMap;
Coordinates kSink;
Coordinates kSource;
deque<Coordinates> kWaveFront;
vector<Coordinates> kTraceBack;

LeeBase::LeeBase() {

}

LeeBase::~LeeBase() {

}

LeeBase::LeeBase(Maps *m) {
    kMap = m;
}

LeeBase &LeeBase::set_map(Maps *m) {
    kMap = m;
    return *this;
}

void LeeBase::start() {
    kSink = kMap->get_sink_coordinates();
    kSource = kMap->get_source_coordinates();

    printf("Starting to run our algorithm\n");
}

LeeBase &LeeBase::set_coordinates(Coordinates s, Coordinates so) {
    kSink = s;
    kSource = so;
    return *this;
}

bool LeeBase::is_sink(Coordinates c) {
    return c.x == kSink.x && c.y == kSink.y;
}

bool LeeBase::is_sink(int x, int y) {
    return kSink.x == x && kSink.y == y;
}

bool LeeBase::is_source(Coordinates c) {
    return c.x == kSource.x && c.y == kSource.y;
}

bool LeeBase::is_source(int x, int y) {
    return kSource.x == x && kSource.y == y;
}

int LeeBase::calculate_manhattan_distance(Coordinates a, Coordinates b) {
    int order1, order2;
    order1 = abs(a.x - b.x);
    order2 = abs(a.y - b.y);
    return order1 + order2;
}

bool LeeBase::is_adjacent(Coordinates a, Coordinates b) {
    if (a.dist == 0) {
        return true;
    }
    int delta_x, delta_y;
    double result = calculate_manhattan_distance(a, b);

    // Calculate the deltas between x and y,
    // this will prevent the diagonal jumping
    delta_x = abs(a.x - b.x);
    delta_y = abs(a.y - b.y);
    // Just for debugging!
    if ((delta_x == 0 && delta_y == 1) || (delta_x == 1 && delta_y == 0)) {
        //printf("Delta_x: %d, Delta_y: %d\n", delta_x, delta_y);
    } else {
        //printf("it's greater than one!\n");
    }
    //printf("---------------------\n");
    // make sure the result is 1 or less and the delta on x or y is 1
    return result <= 1 && (delta_x == 1 || delta_y == 1);
}

bool LeeBase::is_placeable(Coordinates c) {
    // Order matters here!
    if (c.x > kMap->get_map()->size() - 1 || c.x < 0) {
        return false;
    }
    if (c.y > kMap->get_map()->at(0).size() - 1 || c.y < 0) {
        return false;
    }
    if (kMap->get_map()->at(c.x).at(c.y) == Maps::kSource) {
        return false;
    }
    if (kMap->get_map()->at(c.x).at(c.y) == Maps::kUntraversable) {
        return false;
    }
    if (kMap->get_map()->at(c.x).at(c.y) == Maps::kTraceback) {
        return false;
    }
    if (kMap->get_map()->at(c.x).at(c.y) > 0) {
        return false;
    }
    return true;
}

bool LeeBase::is_placeable(int x, int y) {
    Coordinates temp;
    temp.x = x;
    temp.y = y;
    return is_placeable(temp);
}

bool LeeBase::is_adjacent_to_source(Coordinates c) {
    return calculate_manhattan_distance(c, kSource) == 1;
}