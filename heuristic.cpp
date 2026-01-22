#include <vector>
#include <set>
#include "weight.h"
using namespace std;

int evalScore(const vector<vector<int>>& board, int player){
    int score = 0;
    int n = board.size();
    score = getWeight(board, player);
    int permScore = 0;
    //Add score for all tiles that cannot be changed anymore (stable disks)
    vector<vector<bool>> stable(n, vector<bool>(n, false));
    // Check corners
    vector<pair<int, int>> corners = {{0,0}, {0,n-1}, {n-1,0}, {n-1,n-1}};
    for(auto& corner : corners){
        int x = corner.first;
        int y = corner.second;
        if(board[x][y] == player){
            stable[x][y] = true;
            permScore += abs(getWeight(x, y)); // Score for stable corner
            // Expand stability from corner
            int dx = (x == 0) ? 1 : -1;
            int dy = (y == 0) ? 1 : -1;
            for(int i = x; i >= 0 && i < n; i += dx){
                for(int j = y; j >= 0 && j < n; j += dy){
                    if(board[i][j] == player){
                        stable[i][j] = true;
                        permScore += abs(getWeight(i, j)) * 2; // Score for stable edge
                    } else {
                        break;
                    }
                }
            }
        }
    }
    score += permScore;
    return score;
}