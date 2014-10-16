#include <iostream>
#include "Algorithms/Lee/Lee.h"

using namespace std;
//http://www.onlinecompiler.net/sourcecode&id=273
const string file_path = "Maps/";

int main() {
    Lee lee;
    lee.set_lee(1);
    cout << "Lee is: " << lee.get_lee() << endl;

    return 0;
}