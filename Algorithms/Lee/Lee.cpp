using namespace std;

Maps *lee_map;

Coordinates sink_coords;
Coordinates source_coords;

Lee::kLeeType type;

Lee::Lee(Maps* m) {
    lee_map = m;

    type = kLeeType::LEE;

    sink_coords = lee_map->get_sink_coordinates();
    source_coords = lee_map->get_source_coordinates();
}

Lee::Lee(Maps *m, kLeeType a) {
    lee_map = m;

    type = a;

    sink_coords = lee_map->get_sink_coordinates();
    source_coords = lee_map->get_source_coordinates();
}

Lee::~Lee() {}

void Lee::print_map() {
    string output = "";
    vector< vector<int> >::iterator row;
    vector<int>::iterator column;
    vector< vector<int> > *map = lee_map->get_map();
    for(row = map->begin(); row != map->end(); row++) {
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

void Lee::print_queue(deque<Coordinates> *wave_front) {
    string output = "";
    int x = 0;
    for (int x = 0; x < wave_front->size(); x++) {
        output += "R " + to_string(x)
                + ": (" + to_string(wave_front->at(x).x) + ", "
                + to_string(wave_front->at(x).y) + ")\t D: "
                + to_string(wave_front->at(x).dist) + "\n";
        x++;
    }
    char *a = new char[output.size() + 1];
    memcpy(a, output.c_str(), output.size());
    printf("+++++++++++++++++++++\n%s\n+++++++++++++++++++++\n", a);
}

void Lee::print_trace_back(vector<Coordinates> trace_back) {
    string output = "";
    int x = 0;
    for(Coordinates i : trace_back) {
        output += "Record " + to_string(x)
                + ": (" + to_string(i.x) + ", "
                + to_string(i.y) + ")\t Distance: "
                + to_string(i.dist) + "\n";
        x++;
    }
    char *a = new char[output.size()+1];
    memcpy(a,output.c_str(), output.size());
    printf("+++++++++++++++++++++\n%s\n+++++++++++++++++++++\n", a);
}

bool Lee::at_edge(int x, int y, int max) {
    while (max >= 1) {
        if (x - max < -1) {
            return true;
        }
        if (y - max < -1) {
            return true;
        }
        if (x + max > lee_map->get_map()->size()) {
            return true;
        }
        if (y + max > lee_map->get_map()->at(x).size()) {
            return true;
        }
        max--;
    }
    return false;
}

bool Lee::is_placeable(int x, int y) {
    // Order matters here!
    if (x > lee_map->get_map()->size() - 1 || x < 0) {
        return false;
    }
    if (y > lee_map->get_map()->at(0).size() - 1 || y < 0) {
        return false;
    }
    if (lee_map->get_map()->at(x).at(y) == Maps::kSource) {
        return false;
    }
    if (lee_map->get_map()->at(x).at(y) == Maps::kUntraversable) {
        return false;
    }
    if (lee_map->get_map()->at(x).at(y) == Maps::kTraceback) {
        return false;
    }
    if(lee_map->get_map()->at(x).at(y) > 0) {
        printf("Dont need to add: %d,%d\n", x, y);
        return false;
    }
    return true;
}

bool Lee::is_sink(Coordinates c) {
    return (c.x == sink_coords.x) && (c.y == sink_coords.y);
}

bool Lee::is_source(Coordinates c) {
    return (c.x == source_coords.x) && (c.y == source_coords.y);
}

int Lee::calculate_euclidean_distance(int x, int y) {
    // Source is always (x1, y1)
    int order1, order2;
    order1 = (source_coords.x - x)*(source_coords.x - x);
    order2 = (source_coords.y - y)*(source_coords.y - y);
    // http://stackoverflow.com/questions/9695329/c-how-to-round-a-double-to-an-int
    return (int) (sqrt(order1 + order2) + .5);
}

int Lee::calculate_manhattan_distance(int x, int y) {
    int order1, order2;
    order1 = abs(x - source_coords.x);
    order2 = abs(y - source_coords.y);
    return order1 + order2;
}

int Lee::calculate_manhattan_distance(Coordinates curr, Coordinates prev) {
    int order1, order2;
    order1 = abs(curr.x - prev.x);
    order2 = abs(curr.y - prev.y);
    return order1 + order2;
}

int Lee::get_element_at(int x, int y) {
    return lee_map->get_map()->at(x).at(y);
}

bool Lee::is_adjacent(Coordinates curr, Coordinates prev) {
    // If it's the source, add it!
    if (curr.dist == 0) {
        return true;
    }
    int delta_x, delta_y;
    double result;
    result = calculate_manhattan_distance(curr, prev);

    //printf("is Current(%d, %d) close to Previous(%d, %d), it is: %f away\n",
    //        curr.x, curr.y, prev.x, prev.y, result);
    // Calculate the deltas between x and y,
    // this will prevent the diagonal jumping
    delta_x = abs(curr.x - prev.x);
    delta_y = abs(curr.y - prev.y);
    // Just for debugging!
    if ((delta_x == 0 && delta_y == 1) || (delta_x == 1 && delta_y == 0)) {
        //printf("Delta_x: %d, Delta_y: %d\n", delta_x, delta_y);
    } else {
        //printf("it's greater than one!\n");
    }
    //printf("---------------------\n");
    // make sure the result is 1 or less and the delta on x or y is 1
    return result <= 1.0 && (delta_x == 1 || delta_y == 1);
}

void Lee::calculate_next_move(deque<Coordinates> *wave_front, int x, int y) {
    Coordinates temp;
    // (x, y+1)
    if (is_placeable(x, y + 1)) {
        temp.x = x;
        temp.y = y + 1;
        switch (type) {
            case LEE:
                temp.dist = calculate_manhattan_distance(temp.x, temp.y);
                break;
            case LEE_3_BIT:
                temp.dist = (calculate_manhattan_distance(temp.x, temp.y) % 3) == 0
                        ? 3 : (calculate_manhattan_distance(temp.x, temp.y) % 3);
                break;
            case LEE_2_BIT:
                // check x, x-1, y, y-1
                break;
        }
        lee_map->get_map()->at(x).at(y + 1) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x,y+1): (%d, %d)\n", x, y + 1);
    }
    // (x, y-1)
    if (is_placeable(x, y - 1)) {
        temp.x = x;
        temp.y = y - 1;
        switch (type) {
            case LEE:
                temp.dist = calculate_manhattan_distance(temp.x, temp.y);
                break;
            case LEE_3_BIT:
                temp.dist = (calculate_manhattan_distance(temp.x, temp.y) % 3) == 0
                        ? 3 : (calculate_manhattan_distance(temp.x, temp.y) % 3);
                break;
            case LEE_2_BIT:
                // check x, x-1, y, y+1
                break;
        }
        lee_map->get_map()->at(x).at(y - 1) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x,y-1): (%d, %d)\n", x, y - 1);
    }
    // (x+1, y)
    if (is_placeable(x + 1, y)) {
        temp.x = x + 1;
        temp.y = y;
        switch (type) {
            case LEE:
                temp.dist = calculate_manhattan_distance(temp.x, temp.y);
                break;
            case LEE_3_BIT:
                temp.dist = (calculate_manhattan_distance(temp.x, temp.y) % 3) == 0
                        ? 3 : (calculate_manhattan_distance(temp.x, temp.y) % 3);
                break;
            case LEE_2_BIT:
                // check x, x-1, y, y-1
                break;
        }
        lee_map->get_map()->at(x + 1).at(y) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x+1,y): (%d, %d)\n", x + 1, y);
    }
    // (x-1, y)
    if (is_placeable(x - 1, y)) {
        temp.x = x - 1;
        temp.y = y;
        switch (type) {
            case LEE:
                temp.dist = calculate_manhattan_distance(temp.x, temp.y);
                break;
            case LEE_3_BIT:
                temp.dist = (calculate_manhattan_distance(temp.x, temp.y) % 3) == 0
                        ? 3 : (calculate_manhattan_distance(temp.x, temp.y) % 3);
                break;
            case LEE_2_BIT:
                break;
        }
        lee_map->get_map()->at(x - 1).at(y) = temp.dist;
        wave_front->push_back(temp);
        printf("Adding (x-1,y): (%d, %d)\n", x - 1, y);
    }
}

int Lee::get_bit_assignment(int x, int y) {
    Coordinates temp;
    // this gives us our direction
    // +diff means right side, -diff means left side
    int diff_x = source_coords.x - x;
    // +diff means bottom, -diff means top
    int diff_y = source_coords.y - y;
    int ones = 0, twos = 0;
    int answer = 0;
    kDirections d;

    int size_x = lee_map->get_map()->size();
    int size_y = lee_map->get_map()->at(x).size();

    if (x == 0) {
        if (y > 0) {
            d = BOTTOM;
        } else {
            d = TOP;
        }
    }
    else if (y == 0) {
        if (x > 0) {
            d = RIGHT;
        } else {
            d = LEFT;
        }
    }
    else if (diff_x > 0 && diff_y > 0) {
        d = kDirections::TOP_LEFT;
    } else if (diff_x > 0 && diff_y < 0) {
        d = kDirections::BOTTOM_LEFT;
    } else if (diff_x < 0 && diff_y < 0) {
        d = kDirections::BOTTOM_RIGHT;
    } else if (diff_x < 0 && diff_y > 0) {
        d = kDirections::TOP_RIGHT;
    }

    //printf("GBA Sources Coordinates: %d, %d\n", source_coords.x, source_coords.y);
    printf("GBA Current Coordinates: %d, %d\n", x, y);
    //printf("GBA General form of slope: %d, %d\n", x, y);

    /***********************************
    * if you don't have a x,y+/-1, look at x+/-1,y and x+/-2,y
    *   If there isn't a number in either the vertical, look horizontal
    * if you don't have a x+/-1,y, look at x,y+/-1 and x,y+/-2
    * otherwise look at x+/-1,y+/-1, x+/-1,y, and x,y+/-1
    ***********************************/
    /*if (!at_edge(x, y, 2)) {
        switch (d) {
            case TOP:
                // x=0, y--
                get_element_at(x, y - 1) == 1 ? ones++ : 0;
                get_element_at(x, y - 2) == 1 ? ones++ : 0;
                get_element_at(x, y - 1) == 2 ? twos++ : 0;
                get_element_at(x, y - 2) == 2 ? twos++ : 0;
                break;
            case BOTTOM:
                // x=0, y++
                get_element_at(x, y + 1) == 1 ? ones++ : 0;
                get_element_at(x, y + 2) == 1 ? ones++ : 0;
                get_element_at(x, y + 1) == 2 ? twos++ : 0;
                get_element_at(x, y + 2) == 2 ? twos++ : 0;
                break;
            case RIGHT:
                // x--, y=0
                get_element_at(x - 1, y) == 1 ? ones++ : 0;
                get_element_at(x - 2, y) == 1 ? ones++ : 0;
                get_element_at(x - 1, y) == 2 ? twos++ : 0;
                get_element_at(x - 2, y) == 2 ? twos++ : 0;
                break;
            case LEFT:
                // x++, y=0
                get_element_at(x + 1, y) == 1 ? ones++ : 0;
                get_element_at(x + 2, y) == 1 ? ones++ : 0;
                get_element_at(x + 1, y) == 2 ? twos++ : 0;
                get_element_at(x + 2, y) == 2 ? twos++ : 0;
                break;
        }
        // check the +1/-1 case
    } else {
        switch (d) {
            case TOP_LEFT:
                //++x, ++y
                get_element_at(x + 1, y + 1) == 1 ? ones++ : 0;
                get_element_at(x + 1, y) == 1 ? ones++ : 0;
                get_element_at(x, y + 1) == 1 ? ones++ : 0;
                get_element_at(x, y + 1) == 2 ? twos++ : 0;
                get_element_at(x + 1, y) == 2 ? twos++ : 0;
                get_element_at(x + 1, y + 1) == 2 ? twos++ : 0;
                break;
            case TOP_RIGHT:
                //--x, --y
                get_element_at(x - 1, y - 1) == 1 ? ones++ : 0;
                get_element_at(x - 1, y) == 1 ? ones++ : 0;
                get_element_at(x, y - 1) == 1 ? ones++ : 0;
                get_element_at(x, y - 1) == 2 ? twos++ : 0;
                get_element_at(x - 1, y) == 2 ? twos++ : 0;
                get_element_at(x - 1, y - 1) == 2 ? twos++ : 0;
                break;
            case BOTTOM_LEFT:
                //++x, --y
                get_element_at(x + 1, y - 1) == 1 ? ones++ : 0;
                get_element_at(x + 1, y) == 1 ? ones++ : 0;
                get_element_at(x, y - 1) == 1 ? ones++ : 0;
                get_element_at(x, y - 1) == 2 ? twos++ : 0;
                get_element_at(x + 1, y) == 2 ? twos++ : 0;
                get_element_at(x + 1, y - 1) == 2 ? twos++ : 0;
                break;
            case BOTTOM_RIGHT:
                //--x, ++y
                get_element_at(x - 1, y + 1) == 1 ? ones++ : 0;
                get_element_at(x - 1, y) == 1 ? ones++ : 0;
                get_element_at(x, y + 1) == 1 ? ones++ : 0;
                get_element_at(x, y + 1) == 2 ? twos++ : 0;
                get_element_at(x - 1, y) == 2 ? twos++ : 0;
                get_element_at(x - 1, y + 1) == 2 ? twos++ : 0;
                break;
        }
    }*/
    ones > twos ? answer = 1 : answer = 2;
    printf("GBA Returning with an answer of: %d\n", answer);
    return answer;
}

void Lee::calculate_next_move_2_bit(deque<Coordinates> *wave_front, Coordinates curr) {
    Coordinates temp;

    // we do it this way because this is default case
    if (!is_source(curr)) {
        if (is_placeable(curr.x + 1, curr.y)) {
            temp.x = curr.x + 1;
            temp.y = curr.y;
            temp.dist = get_bit_assignment(temp.x, temp.y);
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        if (is_placeable(curr.x - 1, curr.y)) {
            temp.x = curr.x - 1;
            temp.y = curr.y;
            temp.dist = get_bit_assignment(temp.x, temp.y);
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        if (is_placeable(curr.x, curr.y + 1)) {
            temp.x = curr.x;
            temp.y = curr.y + 1;
            temp.dist = get_bit_assignment(temp.x, temp.y);
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        if (is_placeable(curr.x, curr.y - 1)) {
            temp.x = curr.x;
            temp.y = curr.y - 1;
            temp.dist = get_bit_assignment(temp.x, temp.y);
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }

        // else !is_source(curr))
    } else {
        if (is_placeable(curr.x + 1, curr.y)) {
            temp.x = curr.x + 1;
            temp.y = curr.y;
            temp.dist = 1;
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        if (is_placeable(curr.x - 1, curr.y)) {
            temp.x = curr.x - 1;
            temp.y = curr.y;
            temp.dist = 1;
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        if (is_placeable(curr.x, curr.y + 1)) {
            temp.x = curr.x;
            temp.y = curr.y + 1;
            temp.dist = 1;
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        if (is_placeable(curr.x, curr.y - 1)) {
            temp.x = curr.x;
            temp.y = curr.y - 1;
            temp.dist = 1;
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        // Grab the diagonals in this case.
        if (is_placeable(curr.x + 1, curr.y + 1)) {
            temp.x = curr.x + 1;
            temp.y = curr.y + 1;
            temp.dist = 1;
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        if (is_placeable(curr.x - 1, curr.y - 1)) {
            temp.x = curr.x - 1;
            temp.y = curr.y - 1;
            temp.dist = 1;
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        if (is_placeable(curr.x - 1, curr.y + 1)) {
            temp.x = curr.x - 1;
            temp.y = curr.y + 1;
            temp.dist = 1;
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
        if (is_placeable(curr.x + 1, curr.y - 1)) {
            temp.x = curr.x + 1;
            temp.y = curr.y - 1;
            temp.dist = 1;
            wave_front->push_back(temp);
            lee_map->get_map()->at(temp.x).at(temp.y) = temp.dist;
        }
    }
}


void Lee::start() {
    deque<Coordinates> wave_front;
    vector<Coordinates> trace_back;

    Coordinates temp;

    int x = lee_map->get_source_coordinates().x;
    int y = lee_map->get_source_coordinates().y;

    temp.x = x;
    temp.y = y;
    temp.dist = 0;

    wave_front.push_back(temp);

    switch (type) {
        case kLeeType::LEE:
            run_original_lee(&wave_front, &trace_back, 0);
            break;
        case kLeeType::LEE_2_BIT:
            run_2_bit_lee(&wave_front, &trace_back, 0);
            break;
        case kLeeType::LEE_3_BIT:
            run_3_bit_lee(&wave_front, &trace_back, 0);
            break;
    }

    // this is sort of cheating...
    lee_map->get_map()->at(sink_coords.x).at(sink_coords.y) = Maps::kTraceback;

    // Clean the map to make it look nicer
    //lee_map->zero_out_map();

    // print our solution!
    print_trace_back(trace_back);
}

void Lee::run_2_bit_lee(deque<Coordinates> *wave_front, vector<Coordinates> *trace_back, int iteration) {
    printf("//\\\\//\\\\//\\\\//\\\\//\\\\/\n");
    printf("We are on iteration: %d\n", iteration);
    //printf("Sink's coordinates are: (%d, %d)\n", sink_coords.x, sink_coords.y);

    // Base case 1: Not finding a solution
    printf("size of queue: %lu\n", wave_front->size());
    //print_queue(wave_front);
    if (wave_front->size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return;
    }

    // Grab the first record
    Coordinates curr = wave_front->front();
    // pop off the first record
    wave_front->pop_front();

    // Base case 2: We found the sink
    if (is_sink(curr)) {
        printf("We found: (%d, %d) in %d moves\n",
                sink_coords.x, sink_coords.y, (int) floor(iteration / 4) - 1);
        printf("=====================\n\n");
        // add the sink to the trace_back
        trace_back->push_back(curr);
        return;
    }

    // Case 3: We still have places on the map to visit
    //printf("Current coordinates: (%d, %d)\t Distance: %d\n", curr.x, curr.y, curr.dist);

    /**
    * Check each possibility of the next wavefront
    */
    printf("*********************\n");
    calculate_next_move_2_bit(wave_front, curr);
    printf("*********************\n");
    print_map();
    printf("//\\\\//\\\\//\\\\//\\\\//\\\\/\n\n");

    run_2_bit_lee(wave_front, trace_back, iteration + 1);

    // This is the last "portion" that needs to be fixed.
    // note: check to see if it is completely adjacent, not
    // just within one of distance.
    if (trace_back->size() > 0 && curr.dist <= trace_back->back().dist
            && is_adjacent(curr, trace_back->back())) {
        //trace_back->push_back(curr);
        //lee_map->get_map()->at(curr.x).at(curr.y) = Maps::kTraceback;
    }
}

void Lee::run_3_bit_lee(deque<Coordinates> *wave_front, vector<Coordinates> *trace_back, int iteration) {
    printf("We are on iteration: %d\n", iteration);
    printf("Sink's coordinates are: (%d, %d)\n", sink_coords.x, sink_coords.y);

    // Base case 1: Not finding a solution
    printf("size of queue: %lu\n", wave_front->size());
    if (wave_front->size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return;
    }

    // Grab the first record
    Coordinates curr = wave_front->front();
    // pop off the first record
    wave_front->pop_front();

    // Base case 2: We found the sink
    if (is_sink(curr)) {
        printf("We found: (%d, %d) in %d moves\n",
                sink_coords.x, sink_coords.y, (int) floor(iteration / 4) - 1);
        printf("=====================\n\n");
        // add the sink to the trace_back
        trace_back->push_back(curr);
        return;
    }

    // Case 3: We still have places on the map to visit
    printf("*********************\n");
    printf("Current coordinates: (%d, %d)\t Distance: %d\n", curr.x, curr.y, curr.dist);

    /**
    * Check each possibility of the next wavefront
    */
    calculate_next_move(wave_front, curr.x, curr.y);
    print_map();
    printf("=====================\n\n");

    run_3_bit_lee(wave_front, trace_back, iteration + 1);

    // Handle the trace_back generation for the algorithm
    if (trace_back->size() > 0) {
        if (trace_back->back().dist == 1) {
            // Handle the 3->1 hand off
            if (curr.dist == 3 && is_adjacent(curr, trace_back->back())) {
                trace_back->push_back(curr);
                lee_map->get_map()->at(curr.x).at(curr.y) = Maps::kTraceback;
            }
            // Otherwise just decrement as you should
        } else {
            if (curr.dist < trace_back->back().dist && is_adjacent(curr, trace_back->back())) {
                trace_back->push_back(curr);
                lee_map->get_map()->at(curr.x).at(curr.y) = Maps::kTraceback;
            }
        }
    }
}

void Lee::run_original_lee(deque<Coordinates> *wave_front, vector<Coordinates> *trace_back, int iteration) {
    printf("We are on iteration: %d\n", iteration);
    printf("Sink's coordinates are: (%d, %d)\n", sink_coords.x, sink_coords.y);

    // Base case 1: Not finding a solution
    printf("size of queue: %lu\n", wave_front->size());
    if(wave_front->size() < 1) {
        printf("We have nothing in our queue\n");
        printf("=====================\n\n");
        return;
    }

    // Grab the first record
    Coordinates curr = wave_front->front();
    // pop off the first record
    wave_front->pop_front();

    // Base case 2: We found the sink
    if (is_sink(curr)) {
        printf("We found: (%d, %d) in %d moves\n",
                sink_coords.x, sink_coords.y, (int)floor(iteration/4)-1);
        printf("=====================\n\n");
        // add the sink to the trace_back
        trace_back->push_back(curr);
        return;
    }

    // Case 3: We still have places on the map to visit
    printf("*********************\n");
    printf("Current coordinates: (%d, %d)\t Distance: %d\n", curr.x, curr.y, curr.dist);

    /**
    * Check each possibility of the next wavefront
    */
    calculate_next_move(wave_front, curr.x, curr.y);
    print_map();
    printf("=====================\n\n");

    run_original_lee(wave_front, trace_back, iteration + 1);

    // Start the trace_back!
    if(trace_back->size() > 0 && curr.dist <= trace_back->back().dist
            && is_adjacent(curr, trace_back->back())) {
        trace_back->push_back(curr);
        lee_map->get_map()->at(curr.x).at(curr.y) = Maps::kTraceback;
    }
}
