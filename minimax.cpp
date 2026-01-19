#include <vector>
#include <set>
#include "weight.h"
#include "reversi.h"
using namespace std;

const int inf = 1e9;
const int MAX_DEPTH = 6;

//      i, j, score
int minimax(int depth, int a, int b, int player){   //player: 1/-1
    if(depth == 0){

    }

    int i, j;

    if(depth == 0 || hasWinner()){
            if(depth == 0){
                return {NULL, NULL, getWeight(i, j)};
            }
            return {NULL, NULL, inf};
    }
    
    if(player+1){   // 2 or 0
        int value = -player*inf;
        auto validmove = getvalidmove(board, player);
        
        for(auto validmove : getvalidmove(board, player)){
            for(tie [i, j] : validmove){
                auto [_, _, score] = minimax(boardcopy(i, j), depth-1, a, b, -player);
            }
        }
        return {i, j, value};
        
    }else{
        
        int value = player*inf;
        auto [_, _, score] = minimax(boardcopy, depth-1, a, b, -player);
    }
}


pair<int, int> callAI(int player){
    set<pair<int, int>> validmove = getvalidmove(player);
    int best_i = -1, best_j = -1;
    int best_score = -player*inf;
    for(auto [i, j] : validmove){
        int score = minimax(MAX_DEPTH, -inf, inf, -player);
        if(score > best_score){
            best_score = score;
            best_i = i;
            best_j = j;
        }
    }
    return {best_i, best_j};
}