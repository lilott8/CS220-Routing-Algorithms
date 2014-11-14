#include <iostream>
#include "Algorithms/Lee/Lee.h"
#include "Algorithms/LeeOriginal/LeeOriginal.h"
#include "Algorithms/Hadlock/Hadlock.h"
#include "Algorithms/Lee2Bit/Lee2Bit.h"
#include "Algorithms/Lee3Bit/Lee3Bit.h"
#include "Algorithms/Ruben/Ruben.h"

using namespace std;

enum MapType {
    RANDOM, TEST, TXT
};

enum Algorithm {
    LEE2BIT, LEE3BIT, KORN, HADLOCK, RUBEN, LEE
};

Maps *do_random();

Maps *do_file(string);

Maps *do_test();

MapType resolve_map_type(string);

Algorithm resolve_algorithm(string);

int main(int argc, char *argv[]) {

    MapType m_type;
    Algorithm a_type;
    string file = "easy.txt";
    double korn_modifier = 1.5;

    Maps *map;

    // There is a rogue argument, so I just have to account for it.
    switch (argc) {
        case 1:
        default:
            a_type = LEE;
            m_type = TEST;
            break;
        case 2:
            a_type = resolve_algorithm(argv[1]);
            m_type = TEST;
            break;
        case 3:
            a_type = resolve_algorithm(argv[1]);
            m_type = resolve_map_type(argv[2]);
            break;
        case 4:
            a_type = resolve_algorithm(argv[1]);
            m_type = resolve_map_type(argv[2]);
            file = argv[3];
            break;
        case 5:
            a_type = resolve_algorithm(argv[1]);
            m_type = resolve_map_type(argv[2]);
            file = argv[3];
            korn_modifier = atof(argv[4]);
            break;
    }

    switch (m_type) {
        case RANDOM:
            map = do_random();
            break;
        case TXT:
            map = do_file(file);
            break;
        case TEST:
        default:
            map = do_test();
            break;
    }

    /**
    * TODO: Figure out how to do variable derivation
    * This is because I can't figure out how to do
    * parent->child instantiation
    */
    LeeOriginal lo = LeeOriginal(map);
    Lee2Bit l2 = Lee2Bit(map);
    Lee3Bit l3 = Lee3Bit(map);
    Ruben r = Ruben(map);
    Hadlock h = Hadlock(map);

    switch (a_type) {
        case LEE:
        default:
            printf("Using Lee's Algorithm\n");
            lo.start();
            break;
        case LEE2BIT:
            printf("Using Lee's 2-bit Algorithm\n");
            l2.start();
            break;
        case LEE3BIT:
            printf("Using Lee's 3-Bit Algorithm\n");
            l3.start();
            break;
        case KORN:
            //*object = Korn(map);
            // object.set_overpull(korn_modifier);
            printf("Nothing for KORN yet");
            break;
        case RUBEN:
            printf("Using Ruben's Algorithm\n");
            r.start();
            break;
        case HADLOCK:
            printf("Using Hadlock's Algorithm\n");
            h.start();
            break;
    }
    printf("-------------------------\n");
    map->print_map();

    return 0;
}

MapType resolve_map_type(string a) {
    printf("Map is: %s\n", a.c_str());
    if (a.compare("file") == 0) {
        return TXT;
    }
    if (a.compare("random") == 0) {
        return RANDOM;
    }
    if (a.compare("test") == 0) {
        return TEST;
    }
    return TEST;
}

Algorithm resolve_algorithm(string a) {
    if (a.compare("ruben") == 0) {
        return RUBEN;
    }
    if (a.compare("korn") == 0) {
        return KORN;
    }
    if (a.compare("hadlock") == 0) {
        return HADLOCK;
    }
    if (a.compare("lee3bit") == 0) {
        return LEE3BIT;
    }
    if (a.compare("lee2bit") == 0) {
        return LEE2BIT;
    }
    if (a.compare("lee") == 0) {
        return LEE;
    }
    return LEE;
}

Maps *do_random() {
    printf("Generating a random map\n");
    Maps *random_map = new Maps(10);
    return random_map;
}

Maps *do_test() {
    printf("Generating a test map\n");
    // The sink/source are always in the same spot
    Maps *debug_map = new Maps();
    debug_map->set_difficulty(7)
            .set_sink(0, 6)
            .set_source(3, 3);
    return debug_map;
}

Maps *do_file(string fn) {
    printf("Generating a map from file: %s\n", fn.c_str());
    Maps *file_map = new Maps(fn);
    return file_map;
}