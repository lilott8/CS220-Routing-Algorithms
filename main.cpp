#include <iostream>
#include "Algorithms/Lee/Lee.h"
#include "Maps/Maps.h"

using namespace std;
//http://www.onlinecompiler.net/sourcecode&id=273
const string file_path = "Maps/";

int main() {
    Lee lee;
    Maps map(10);
    map.print_map();
    lee.set_lee(1);
    //cout << "Lee is: " << lee.get_lee() << endl;

    return 0;
}