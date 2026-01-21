#include <vector>
#include <set>
#include <stack>
#include "weight.h"
#include "core/reversi.h"
using namespace std;

pair<int, int> callAI(const Board& gameBoard, int player);

int minimax(Board& virtualBoard, int depth, int a, int b, int player, int isMax, int rootPlayer);
