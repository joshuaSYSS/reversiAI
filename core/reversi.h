#include <vector>
#include <set>
using namespace std;

set<pair<int, int>> getvalidmove(int);
void place(int, int, int);
vector<vector<int>> getBoard();
int hasWinner();
void printBoard();