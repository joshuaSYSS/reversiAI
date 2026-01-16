#include <vector>
#include <set>
using namespace std;


vector<vector<int>> directions= {{1, -1}, {1, 0}, {1, 1}, 
	                            {0, -1}         , {0, 1}, 
	                            {-1, -1}, {-1, 0}, {-1, 1}};

bool isavailable(vector<vector<int>>& board, int player, int i, int j,  direction){
    //if not in range and its not == to opponent then  NULL
    if(i>=0 && i<8 && j>=0 && j<8){
        if(board[i][j] == -player)
            return isavailable(board, player, i+direction.at(0), j+direction.at(1), direction);
        else if(board[i][j] == 0)
            return {i, j};
    }
    
    return NULL;
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

//      i, j, score
tuple<int, int, int> minimax(vector<vector<int>>& board, int depth, int a, int b, int player){   //player: 1/-1
    int i, j;

    if(depth == 0 || hasWinner(board, i, j, player)){
            if(depth == 0){
                return {NULL, NULL, getScore(i, j)};
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
