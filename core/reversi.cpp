#include <vector>
#include <set>
#include <optional>
#include <iostream>

using namespace std;

const int BOARD_SIZE = 8;
//static vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

static vector<vector<int>> board  = {
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 1, -1, 0, 0, 0},
        { 0, 0, 0, -1, 1, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0}
    };

const int DIRECTION_SIZE = 8;
const vector<pair<int, int>> DIRECTIONS =	{{1, -1},	{1, 0},		{1, 1},
											{0, -1},				{0, 1},
											{-1, -1},	{-1, 0},	{-1, 1}
};

//not placed: 0
//player 1: 1
//player 2: -1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

optional<pair<int, int>> availablefield(vector<vector<int>>& board, int player, int i, int j, pair<int, int> direction, bool op_found=0) {
	int x = i + direction.first, y = j + direction.second;

	if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)	return nullopt;
	if(board[x][y] == 0)	return op_found ? optional{pair{x, y}} : nullopt;
	if(board[x][y] == -player)	return availablefield(board, player, x, y, direction, 1);
	return nullopt;
}

set<pair<int, int>> getvalidmove(int player) {
	set<pair<int, int>> validmove;
	
	for(int i=0; i<BOARD_SIZE; i++)
		for(int j=0; j<BOARD_SIZE; j++)
			if(board[i][j]==player)
				for(auto& d : DIRECTIONS)
					if(auto result = availablefield(board, player, i, j, d))
						validmove.insert(*result);
	return validmove;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool reverse(vector<vector<int>>& board, int player, int i, int j, pair<int, int> direction) {
	int x = i + direction.first, y = j + direction.second;

	if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] == 0)	return false;
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
	for(auto& d: DIRECTIONS) reverse(board, player, i, j, d);	//check for each direction, reverse all opponent chess between the two self chesses "o x x o"
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//返回值:	2= 黑 贏 | -2= o=白 贏 | 0= 平局 | 1= 黑 繼續 | -1= 白 繼續
int determineWinner() {
    int sum = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
            sum += board[i][j];
    return sum > 0 ? 2 : (sum < 0 ? -2 : 0);
}

int hasWinner(int player) {
    for(const auto& row : board)
        for(int cell : row)
            if(cell == 0)
                goto not_full;
    return determineWinner();
not_full:
    if(!getvalidmove(-player).empty()) return -player;
    if(!getvalidmove(player).empty()) return player;
    return determineWinner();
}

/*
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
}*/

//if player 
//condition 1: all squares are filled
//condition 2: both players cannot place
/*
int hasWinner(){
	//condition 1
	int isFULL = 1;
	for(int i = 0; i < BOARD_SIZE;i++){
		for(int j = 0; j < BOARD_SIZE;j++){
			if(!board[i][j]) {isFULL = 0; break;}
		}
		if(!isFULL) break;
	}
	if(isFULL) {
		return determineWinner();
	}

	//condition 2
	int a = 0; //player 1
	int b = 0; //player 2
	for(int i=0; i<BOARD_SIZE; i++)
		for(int j=0; j<BOARD_SIZE; j++)
			if(!board[i][j]){
				auto validmove1 = getvalidmove(1);
				auto validmove2 = getvalidmove(-1);
				if(!validmove1.empty()) a = 1;
				if(!validmove2.empty()) b = 1;
			}
	if(!a && !b){
		return determineWinner();
	}
	
	if()
}*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<int>> getBoard() {
	return board;
}

void printBoard(int showplayermove=0){
	vector<vector<int>> boardcopy = board;
	if(showplayermove){	
		auto validmove = getvalidmove(showplayermove);
		for(auto& move: validmove){
			boardcopy[move.first][move.second] = 2;
		}
	}
	cout << "  ";
	for(int j = 0; j < BOARD_SIZE; j++){
		cout << j << " ";
	}
	cout << endl;
	for(int i = 0; i < BOARD_SIZE; i++){
		cout << i << " ";
		for(int j = 0; j < BOARD_SIZE; j++){
			switch(boardcopy[i][j]){
				case 1: 	cout << "x ";	break;
				case -1: 	cout << "o ";	break;
				case 2:		cout << ". ";	break;
				default:	cout << ". ";
			}
		}
		cout << endl;
	}
}
