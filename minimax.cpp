#include <vector>
#include <set>
#include "weight.h"
#include "reversi.h"
using namespace std;

const int inf = 1e9;
const int MAX_DEPTH = 4;

vector<vector<int>> board;

//undo
//TO-DO

//      i, j, score
int minimax(int depth, int a, int b, int player, int isMax){   //player: 1/-1
    if(depth == 0){
        int score;
        //compute score
        return score;
    }
    
    if(isMax){
        int maxEval = -inf;
        set<pair<int, int>> validmove = getvalidmove(player);
        for(auto [i, j] : validmove){

            int eval = minimax(depth - 1, a, b, -player, 0);

            maxEval = max(maxEval, eval);
            a = max(a, eval);
            if(b <= a)
                break;
        }
        return maxEval;
        
    }
    else{

    }
}


pair<int, int> callAI(int player){
    board = getBoard();
    set<pair<int, int>> validmove = getvalidmove(player);
    int best_i = -1, best_j = -1;
    int best_score = -player*inf;
    for(auto [i, j] : validmove){
        int score = minimax(MAX_DEPTH, -inf, inf, -player, 1);
        if(score > best_score){
            best_score = score;
            best_i = i;
            best_j = j;
        }
    }
    return {best_i, best_j};
}