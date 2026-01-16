#include <vector>
using namespace std;

vector<vector<int>> available();
void place(int, int, int);
void flip();
bool isavailable(vector<vector<int>>&, int, int, int, pair<int, int>);
vector<vector<int>> getBoard();