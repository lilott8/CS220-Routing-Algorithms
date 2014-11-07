#include <iostream>
#include "Algorithms/Lee/Lee.h"
#include "Algorithms/LeeOriginal/LeeOriginal.h"

using namespace std;

int main() {

    bool use_random = false;
    bool use_debug = true;

    if(use_random) {
        printf("Using random map\n");
        Maps *random_map = new Maps(10);
        //Lee lee(random_map, Lee::LEE);
        LeeOriginal lee(random_map);
        lee.start();
        //lee.print_map();
        random_map->print_map();
        delete(random_map);
    }

    if(use_debug) {
        printf("using debug map\n\n");
        // The sink/source are always in the same spot
        Maps *debug_map = new Maps();
        debug_map->set_difficulty(7)
                .set_sink(0, 6)
                .set_source(3, 3);

        //Lee lee(debug_map, Lee::LEE_3_BIT);
        LeeOriginal lee(debug_map);

        lee.start();

        debug_map->print_map();

        delete(debug_map);
    }

    return 0;
}