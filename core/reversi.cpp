#include <vector>
using namespace std;

const int BOARD_SIZE = 8;

const int DIRECTION_SIZE = 8;
const vector<pair<int, int>> DIRECTIONS = {{1, -1}, {1, 0}, {1, 1}, 
	                            {0, -1}         , {0, 1}, 
	                            {-1, -1}, {-1, 0}, {-1, 1}};

vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
//not placed: 0
//player 1: 1
//player 2: -1

bool reverse(vector<vector<int>>& board, int player, int i, int j, pair<int, int> direction){
	int x = i + direction.first, y = j + direction.second;
	
    if(x < 0 || x >= 8 || y < 0 || y >= 8 || board[x][y] == 0)	return false;
    if(board[x][y] == -player){
        if(reverse(board, player, x, y, direction)){
            board[x][y] = player;
            return true;
        }
    }
    return (board[x][y] == player);
}

void place(int i, int j, int player){
    board[i][j] = player;
	for(auto& d: DIRECTIONS)	reverse(board, player, i, j, d);	//check for each direction, reverse all oponent chess between the two self chesses "o x x o"
}
//	above <-- version 2

void place(int i, int j, int player){
    board[i][j] = player;
    
    vector<bool> b = reversible_direaction(board, player, i, j);
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
/*
vector<bool> reversible_direaction(vector<vector<int>>& board, int player, int i, int j) {
	vector<bool> b;
	for(auto d : directions){
		do{	int x=i+direction.first; y=j+direction.second;
		  }while(x>=0 && y<8 && x>=0 && y<8 && board[x][y] == -player);
		if(board[x][y] == player)	b.pushback(1);
		else	b.pushback(0);
	}	
}
*/

vector<bool> isavailable(vector<vector<int>>& board, int player, int i, int j) {
	//if not in range and its not == to opponent then  NULL
	if(i>=0 && i<8 && j>=0 && j<8) {
		if(board[i][j] == -player)
			return isavailable(board, player, i+direction.first, j+direction.second);
		else if(board[i][j] == 0)
			return true;
	}

	return false;
}

vector<pair<int,int>> getvalidmove(vector<vector<int>>& board, int player){
    vector<pair<int, int>> validmove;
    
    for(int block:board){
        if(block==player){
            for(auto d : directions){
                if(isavailable(board, player, i, j, direction))
                validmove.push_back({i, j});
            }
        }
    }
}

vector<vector<int>> getBoard(){
    return board;
}
