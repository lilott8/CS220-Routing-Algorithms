#include <iostream>
#include "Algorithms/Lee/Lee.h"
#include "Maps/Maps.h"
#include "DataStructures/Global.h"

using namespace std;

int main() {
    Maps map(10);
    Lee lee(map);
    lee.start_lee();

    //delete lee;

    map.print_map();
    //cout << "Lee is: " << lee.get_lee() << endl;

    return 0;
}