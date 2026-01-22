#include <vector>
#include <set>
#include "weight.h"
using namespace std;

int evalScore(const vector<vector<int>>& board, int player){
    int score = 0;
    int n = board.size();
    score = getWeight(board, player);
    return score;
}