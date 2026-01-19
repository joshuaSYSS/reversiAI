#include <vector>
using namespace std;
const vector<vector<int>> WEIGHTS = {
    { 128, -64,  32,  16,  16,  32, -64, 128},
    { -64, -96,  -8,  -8,  -8,  -8, -96, -64},
    {  32,  -8,   4,   4,   4,   4,  -8,  32},
    {  16,  -8,   4,   0,   0,   4,  -8,  16},
    {  16,  -8,   4,   0,   0,   4,  -8,  16},
    {  32,  -8,   4,   4,   4,   4,  -8,  32},
    { -64, -96,  -8,  -8,  -8,  -8, -96, -64},
    { 128, -64,  32,  16,  16,  32, -64, 128}
};

int getWeight(const vector<vector<int>>& board, int player) {
    int sum = 0;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            sum += (board[i][j] == 0) ? 0 : (board[i][j] == player) ? WEIGHTS[i][j] : -WEIGHTS[i][j];
        }
    }
    return player*sum;
}
