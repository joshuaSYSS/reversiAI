#include <vector>
#include <set>
#include <optional>
#include <iostream>
#include <stack>
#include "reversi.h"

using namespace std;
	
void Board::refreshBoard() {
	board  = {
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 1, -1, 0, 0, 0},
		{ 0, 0, 0, -1, 1, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0}
	};
}

Board::Board() {
	refreshBoard();
	persistent = stack<vector<pers>>();
}

vector<vector<int>> Board::getBoard() {
	return board;
}

void Board::printBoard(int showplayermove) const{
	vector<vector<int>> displayBoard = board;
	if(showplayermove) {
		auto validmove = getvalidmove(showplayermove);
		for(auto& move: validmove) {
			displayBoard[move.first][move.second] = 2;
		}
	}
	cout << "  ";
	for(int j = 0; j < BOARD_SIZE; j++) {
		cout << j << " ";
	}
	cout << endl;
	for(int i = 0; i < BOARD_SIZE; i++) {
		cout << i << " ";
		for(int j = 0; j < BOARD_SIZE; j++) {
			
			switch(displayBoard[i][j]) {
				case 1: 	cout << "o ";	break; //●
				case -1: 	cout << "x ";	break; //○
				case 2:		cout << ". ";	break; //◦
				default:	cout << ". ";
			}
		}
		cout << endl;
	}
}

void Board::place(int i, int j, int player) {
	p.clear();
	p.push_back({i, j, board[i][j]});
	board[i][j] = player;
	for(auto& d: DIRECTIONS) reverse(player, i, j, d);
	persistent.push(p);
}

bool Board::reverse(int player, int i, int j, pair<int, int> direction) {
	int x = i + direction.first, y = j + direction.second;

	if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] == 0)	return false;
	if(board[x][y] == -player) {
		if(reverse(player, x, y, direction)) {
			p.push_back({x, y, board[x][y]});
			board[x][y] = player;
			return true;
		}
	}
	return (board[x][y] == player);
}

void Board::undo() {
	vector<pers> last_move = persistent.top();
	persistent.pop();
	for(auto mv : last_move) {
		board[mv.i][mv.j] = mv.prev_value;
	}
}

optional<pair<int, int>> Board::availablefield(const vector<vector<int>>& board, int player, int i, int j, pair<int, int> direction, bool op_found) const{
	int x = i + direction.first, y = j + direction.second;

	if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)	return nullopt;
	if(board[x][y] == 0)	return op_found ? optional{pair{x, y}} : nullopt;
	if(board[x][y] == -player)	return availablefield(board, player, x, y, direction, 1);
	return nullopt;
}

set<pair<int, int>> Board::getvalidmove(int player) const{
	set<pair<int, int>> validmove;

	for(int i=0; i<BOARD_SIZE; i++)
		for(int j=0; j<BOARD_SIZE; j++)
			if(board[i][j]==player)
				for(auto& d : DIRECTIONS)
					if(auto result = availablefield(board, player, i, j, d)){
						validmove.insert(*result);
					}
	return validmove;
}

int Board::determineWinner() {
	int sum = 0;
	for(int i = 0; i < BOARD_SIZE; i++)
		for(int j = 0; j < BOARD_SIZE; j++)
			sum += board[i][j];
	return sum > 0 ? 2 : (sum < 0 ? -2 : 0);
}

int Board::hasWinner(int player) {
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
