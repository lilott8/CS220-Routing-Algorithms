#pragma once
#include <deque>
#include "../../Maps/Maps.h"
#include "../../DataStructures/Global.h"

using namespace std;

class Coordinates;
class Maps;

class Lee {

public:
    // Variables
    enum kLeeType {
        LEE, LEE_3_BIT, LEE_2_BIT
    };
    // Constructor
    Lee(Maps*);

    Lee(Maps *, kLeeType);
    ~Lee();
    // Methods
    void start_lee();
    void print_map();
private:
    // Methods
    void run_original_lee(deque<Coordinates> *, vector<Coordinates> *, int);
    void run_2_bit_lee(deque<Coordinates> *, vector<Coordinates> *, int);
    void run_3_bit_lee(deque<Coordinates> *, vector<Coordinates> *, int);
    void print_trace_back(vector<Coordinates>);
    void calculate_next_move(deque<Coordinates> *, int, int);

    void calculate_next_move_2_bit(deque<Coordinates> *, Coordinates);

    void print_queue(deque<Coordinates> *);
    bool check_traversability(int, int);
    bool is_placeable(int, int);
    bool is_adjacent(Coordinates, Coordinates);
    bool is_sink(Coordinates);

    bool is_source(Coordinates);
    int calculate_euclidean_distance(int, int);
    int calculate_manhattan_distance(int, int);
    int calculate_manhattan_distance(Coordinates, Coordinates);

    int get_bit_assignment(Coordinates);
    // Variables
    Maps *lee_map;
    Coordinates sink_coords;
    Coordinates source_coords;

};