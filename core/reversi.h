#ifndef REVERSI_H
#define REVERSI_H
#include <vector>
#include <set>
#include <optional>
#include <iostream>
#include <stack>

using namespace std;

class Board{
public:
	const int BOARD_SIZE = 8;
	const int DIRECTION_SIZE = 8;
	const vector<pair<int, int>> DIRECTIONS =	{{1, -1},	{1, 0},		{1, 1},
												{0, -1},				{0, 1},
												{-1, -1},	{-1, 0},	{-1, 1}};

	vector<vector<int>> board;

	struct pers{
		int i, j;
		int prev_value;
	};
	stack<vector<pers>> persistent;
	vector<pers> p;

	void refreshBoard();

	Board();

	vector<vector<int>> getBoard() ;

	void printBoard(int showplayermove=0) const;

	void place(int i, int j, int player) ;

	bool reverse(int player, int i, int j, pair<int, int> direction);

	void undo();

	bool isValidMove(int player, int i, int j, pair<int, int> direction, bool op_found=0) const;

	vector<pair<int, int>> getvalidmove(int player) const;

	int determineWinner();

	int hasWinner(int player);
	
};

#endif
