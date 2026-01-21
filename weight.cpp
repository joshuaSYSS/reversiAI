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

const int BOARD_SIZE = 8;

int getWeight(const vector<vector<int>>& board, int rootPlayer) {
    int sum = 0;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == rootPlayer) sum += WEIGHTS[i][j];
            else if(board[i][j] == -rootPlayer) sum -= WEIGHTS[i][j];
        }
    }
    return sum;
}
int getWeight(int i, int j){
    return WEIGHTS[i][j];
}
