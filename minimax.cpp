#ifndef MINIMAX_H
#define MINIMAX_H
#include <vector>
#include <set>
#include <algorithm>
#include <stack>
#include <future>
#include "core/reversi.h"
#include "weight.h"
#include "minimax.h"
#include "heuristic.h"


using namespace std;

const int inf = 1e9;
const int MAX_DEPTH = 8;

pair<int, int> callAI(const Board& gameBoard, int player){
    int best_i = -1, best_j = -1;
    int best_score = -inf;
    auto validmove = gameBoard.getvalidmove(player);

    cout << "AI is calculating the best move..." << endl;

    // Store futures for parallel evaluation
    vector<future<pair<int,int>>> futures;

    for(auto [i, j] : validmove){
        futures.push_back(async(launch::async, [&, i, j](){
            Board virtualBoard = gameBoard;
            virtualBoard.place(i, j, player);
            int score = minimax(virtualBoard, MAX_DEPTH - 1, -inf, inf, -player, 0, player);
            virtualBoard.undo();
            return make_pair(score, i*100 + j); // encode move
        }));
    }

    // Collect results
    for(auto &f : futures){
        auto [score, move] = f.get();
        int i = move / 100, j = move % 100;
        if(score > best_score){
            best_score = score;
            best_i = i;
            best_j = j;
        }
    }

    cout << "AI plays: " << best_i << " " << best_j << endl;
    return {best_i, best_j};
}


int minimax(Board& virtualBoard, int depth, int a, int b, int player, int isMax, int rootPlayer){   //player: 1/-1

    vector<pair<int, int>> validmove = virtualBoard.getvalidmove(player);

    if(depth == 0){
        //返回值:	2= 黑 贏 | -2= o=白 贏 | 0= 平局 | 1= 黑 繼續 | -1= 白 繼續
        if(validmove.empty() && virtualBoard.getvalidmove(-player).empty()){
            int winner = virtualBoard.hasWinner(rootPlayer);
            if(winner == 2) return inf;        //rootPlayer wins
            else if(winner == -2) return -inf; //rootPlayer loses
            else return 0;                     //draw
        }
        int score;
        score = evalScore(virtualBoard.getBoard(), rootPlayer);
        return score;
    }

    if(validmove.empty()){
        return minimax(virtualBoard, depth - 1, a, b, -player, 1-isMax, rootPlayer);
    }
    
    if(isMax){
        int maxEval = -inf;
        
        sort(validmove.begin(), validmove.end(), [](pair<int, int> a, pair<int, int> b){
            return getWeight(a.first, a.second) > getWeight(b.first, b.second);
        });

        for(auto [i, j] : validmove){
            virtualBoard.place(i, j, player);
            int eval = minimax(virtualBoard, depth - 1, a, b, -player, 0, rootPlayer);
            virtualBoard.undo();
            maxEval = max(maxEval, eval);
            a = max(a, eval);
            if(b <= a)
                break;
        }
        return maxEval;
    }
    else{
        int minEval = inf;

        sort(validmove.begin(), validmove.end(), [](pair<int, int> a, pair<int, int> b){
            return getWeight(a.first, a.second) < getWeight(b.first, b.second);
        });
        
        for(auto [i, j] : validmove){
            virtualBoard.place(i, j, player);
            int eval = minimax(virtualBoard, depth - 1, a, b, -player, 1, rootPlayer);
            virtualBoard.undo();
            minEval = min(minEval, eval);
            b = min(b, eval);
            if(b <= a)
                break;
        }
        return minEval;
    }
}

#endif
