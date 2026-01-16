#include <vector>
using namespace std;

//not placed: 0
//player 1: 1
//player 2: -1
vector<vector<int>> board(8, vector<int>(8, 0));

vector<vector<int>> getBoard(){
    return board;
}

void place(int i, int j, int player){
    board[i][j] = player;
    
    //Up
    for(int a = i; a >= 0;a--){
        
    }
}