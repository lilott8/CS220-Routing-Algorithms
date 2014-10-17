#include <vector>

using namespace std;

class Maps {
public:
    Maps(int);
    Maps();
    vector<vector<int> > get_map();
    void set_difficulty(int);
    void print_map();
private:
    void initialize_map();
    vector<vector<int> > map;
    void set_points();
    int difficulty;
    bool initialized;
};