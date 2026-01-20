#include <vector>
#include <set>
#include <stack>
#include "weight.h"
#include "core/reversi.h"
using namespace std;

const vector<pair<int, int>> DIRECTIONS =	{{1, -1},	{1, 0},		{1, 1},
											{0, -1},				{0, 1},
											{-1, -1},	{-1, 0},	{-1, 1}
};
const int inf = 1e9;
const int MAX_DEPTH = 12;
const int BOARD_SIZE = 8;

static vector<vector<int>> board;

struct pers{
    int i;
    int j;
    int prev_value;
};

stack<vector<pers>> persistent;

//undo
void undo(){
    vector<pers> last_move = persistent.top();
    persistent.pop();
    for(auto mv : last_move){
        board[mv.i][mv.j] = mv.prev_value;
    }
}

vector<pers> p;
void update(int i, int j){
    persistent.push(p);
}

bool reverse(int player, int i, int j, pair<int, int> direction) {
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

void place1(int i, int j, int player) {
    p.clear();
    p.push_back({i, j, board[i][j]});
	board[i][j] = player;
	for(auto& d: DIRECTIONS) reverse(player, i, j, d);	//check for each direction, reverse all opponent chess between the two self chesses "o x x o"
    update(i, j);
}

//      i, j, score
int minimax(int depth, int a, int b, int player, int isMax){   //player: 1/-1
    if(depth == 0){
        int score;
        score = getWeight(board, player);
        return score;
    }
    
    if(isMax){
        int maxEval = -inf;
        set<pair<int, int>> validmove = getvalidmove(player);
        if(validmove.empty()){
            int eval = minimax(depth, a, b, -player, 0);
            return eval;
        }
        for(auto [i, j] : validmove){
            place1(i, j, player);
            int eval = minimax(depth - 1, a, b, -player, 0);
            undo();
            maxEval = max(maxEval, eval);
            a = max(a, eval);
            if(b <= a)
                break;
        }
        return maxEval;
    }
    else{
        int minEval = inf;
        set<pair<int, int>> validmove = getvalidmove(player);
        if(validmove.empty()){
            int eval = minimax(depth, a, b, -player, 1);
            return eval;
        }
        for(auto [i, j] : validmove){
            place1(i, j, player);
            int eval = minimax(depth - 1, a, b, -player, 1);
            undo();
            minEval = min(minEval, eval);
            b = min(b, eval);
            if(b <= a)
                break;
        }
        return minEval;
    }
}


pair<int, int> callAI(int player){
    board = getBoard();
    persistent = stack<vector<pers>>();
    set<pair<int, int>> validmove = getvalidmove(player);
    int best_i = -1, best_j = -1;
    int best_score = -inf;
    for(auto [i, j] : validmove){
        place1(i, j, player);
        int score = minimax(MAX_DEPTH - 1, -inf, inf, -player, 1);
        undo();
        if(score > best_score){
            best_score = score;
            best_i = i;
            best_j = j;
        }
    }
    return {best_i, best_j};
}