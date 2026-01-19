#include <vector>
#include <set>
#include <optional>

using namespace std;

const int BOARD_SIZE = 8;
vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

const int DIRECTION_SIZE = 8;
const vector<pair<int, int>> DIRECTIONS =	{{1, -1},	{1, 0},		{1, 1},
											{0, -1},				{0, 1},
											{-1, -1},	{-1, 0},	{-1, 1}
};

//not placed: 0
//player 1: 1
//player 2: -1

optional<pair<int, int>> availablefield(vector<vector<int>>& board, int player, int i, int j, pair<int, int> direction, bool op_found=0) {
	int x = i + direction.first, y = j + direction.second;

	if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)	return nullopt;
	if(board[x][y] == 0)	return op_found ? optional{pair{x, y}} : nullopt;
	if(board[x][y] == -player)	return availablefield(board, player, x, y, direction, 1);
	return nullopt;
}

set<pair<int, int>> getvalidmove(vector<vector<int>>& board, int player) {
	set<pair<int, int>> validmove;
	
	for(int i=0; i<BOARD_SIZE; i++)
		for(int j=0; j<BOARD_SIZE; j++)
			if(board[i][j]==player)
				for(auto& d : DIRECTIONS)
					if(auto result = availablefield(board, player, i, j, d))
						validmove.insert(*result);
	return validmove;
}

bool reverse(vector<vector<int>>& board, int player, int i, int j, pair<int, int> direction) {
	int x = i + direction.first, y = j + direction.second;

	if(x < 0 || x >= 8 || y < 0 || y >= 8 || board[x][y] == 0)	return false;
	if(board[x][y] == -player) {
		if(reverse(board, player, x, y, direction)) {
			board[x][y] = player;
			return true;
		}
	}
	return (board[x][y] == player);
}

void place(int i, int j, int player) {
	board[i][j] = player;
	for(auto& d: DIRECTIONS)	reverse(board, player, i, j, d);	//check for each direction, reverse all opponent chess between the two self chesses "o x x o"
}

//	above <-- version 2

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

void place(int i, int j, int player) {
	board[i][j] = player;

	vector<bool> b = reversible_direaction(board, player, i, j);
	for(int d = 0; d < DIRECTION_SIZE; d++) {
		if(b[d]) {
			int x = i + DIRECTIONS[d][0];
			int y = j + DIRECTIONS[d][1];
			while(board[x][y] == -player) {
				board[x][y] = player;
				x += DIRECTIONS[d][0];
				y += DIRECTIONS[d][1];
			}
		}
	}
}

vector<vector<int>> getBoard() {
	return board;
}

int determineWinner(){
	int a = 0; //1
	int b = 0; //-1
	for(int i = 0; i < BOARD_SIZE;i++){
		for(int j = 0; j < BOARD_SIZE;j++){
			if(board[i][j] == 1) a++;
			else if(board[i][j] == -1) b++;
		}
	}
	if(a > b) return 1;
	if(b > a) return -1;
	return 2;
}

//returns the winner 1/-1, if not ended, then return 0. if draw, returns 2
//condition 1: all squares are filled
//condition 2: both players cannot place
int hasWinner(){
	//condition 1
	int ok = 1;
	for(int i = 0; i < BOARD_SIZE;i++){
		for(int j = 0; j < BOARD_SIZE;j++){
			if(!board[i][j]) {ok = 0; break;}
		}
		if(!ok) break;
	}
	if(ok) {
		return determineWinner();
	}

	//condition 2
	int a = 0; //player 1
	int b = 0; //player 2
	for(int i=0; i<BOARD_SIZE; i++)
		for(int j=0; j<BOARD_SIZE; j++)
			if(!board[i][j]){
				auto validmove1 = getvalidmove(board, 1);
				auto validmove2 = getvalidmove(board, -1);
				if(!validmove1.empty()) a = 1;
				if(!validmove2.empty()) b = 1;
			}
	if(!a && !b){
		return determineWinner();
	}
	return 0;
}
