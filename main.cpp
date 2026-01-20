#include <iostream>
#include "core/reversi.h"
#include "minimax.h"
using namespace std;
int main(void){
    int player = 1;
    while(true){
        pair<int, int> move;
        if(player == 1){
            cout << "Your turn (format: row col): ";
            int i, j;
            cin >> i >> j;
            move = {i, j};
        }
        else{
            cout << "AI is thinking..." << endl;
            move = callAI(player);
            cout << "AI plays: " << move.first << " " << move.second << endl;
        }
        place(move.first, move.second, player);
        printBoard();
        int winner = hasWinner();
        if(winner != 0){
            if(winner == 1) cout << "Player 1 wins!" << endl;
            else if(winner == -1) cout << "Player 2 wins!" << endl;
            else cout << "It's a draw!" << endl;
            break;
        }
        player = -player;
    }
  return 0;
}
