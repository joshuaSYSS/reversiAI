#include <vector>
using namespace std;

const int BOARD_SIZE = 8;

const int DIRECTION_SIZE = 8;
const vector<vector<int>> DIRECTIONS = {{1, -1}, {1, 0}, {1, 1}, 
	                            {0, -1}         , {0, 1}, 
	                            {-1, -1}, {-1, 0}, {-1, 1}};

//not placed: 0
//player 1: 1
//player 2: -1
vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

void place(int i, int j, int player){
    board[i][j] = player;
    
    vector<bool> b = isavailable(board, player, i, j);
    for(int d = 0; d < DIRECTION_SIZE; d++){
        if(b[d]){
            int x = i + DIRECTIONS[d][0];
            int y = j + DIRECTIONS[d][1];
            while(board[x][y] == -player){
                board[x][y] = player;
                x += DIRECTIONS[d][0];
                y += DIRECTIONS[d][1];
            }
        }
    }
}

vector<bool> isavailable(vector<vector<int>>& board, int player, int i, int j){

}

vector<vector<int>> getBoard(){
    return board;
}