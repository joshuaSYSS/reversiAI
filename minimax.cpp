


vector<vector<int>> directions= {{1, -1}, {1, 0}, {1, 1}, 
	                            {0, -1}         , {0, 1}, 
	                            {-1, -1}, {-1, 0}, {-1, 1}};

pair<int, int> isavailable(board, player, i, j, direction){
    //not out bound and == -player
    if()
        isavailable(board, player, i+direction.at(0), j+direction.at(1), direction);
    return {i, j};
}


vector<pair<int,int>> getvalidmove(board, int player){
    vector<pair<int>> vaildmove;
    for//each player's chess
        vailmove.add(isavailable(board, player, i, j, direction));
}

//      i, j, score
tuple<int, int, int> minimax(board, depth, a, b, player){   //player: 1/-1
    int i, j;

    if(depth == 0 || if(hasWinner(board, i, j, player)))
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
