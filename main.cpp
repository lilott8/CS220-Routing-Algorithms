#include <iostream>
#include "Algorithms/Lee/Lee.h"
#include "Maps/Maps.h"
#include "Coordinates.h"

using namespace std;

int main() {
    Maps map(10);
    Lee lee(map);
    lee.start_lee();

    map.print_map();
    //cout << "Lee is: " << lee.get_lee() << endl;

    return 0;
}