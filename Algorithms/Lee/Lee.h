#include <deque>
#include "../../Maps/Maps.h"

using namespace std;

class Coordinates;
class Maps;

class Lee {

public:
    // Constructor
    Lee(Maps);
    // Methods
    void start_lee();
    // Variables
private:
    // Methods
    void run_lee(deque<Coordinates>, int);
    // Variables
    Maps lee_map;
    Coordinates sink_coords;
    Coordinates source_coords;
};