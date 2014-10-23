#include <iostream>
#include "Algorithms/Lee/Lee.h"
#include "Maps/Maps.h"
#include "DataStructures/Global.h"

using namespace std;

int main() {
    Maps *map = new Maps(5);
    Lee lee(map);
    lee.start_lee();

    map->print_map();
    printf("=====================================\n");
    lee.print_map();

    delete(map);

    return 0;
}