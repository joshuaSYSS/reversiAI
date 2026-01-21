#include <iostream>
#include "core/reversi.h"
#include "minimax.h"
using namespace std;
int main(void){
    int player = 1;
    Board gameBoard = Board();
    gameBoard.refreshBoard();
    while(true){
        pair<int, int> move = {-1,-1};
        gameBoard.printBoard(player);

        if(player == -1){
            int i, j;
            cout << "Your turn (format: row col): ";
            cin >> i >> j;

            if(i==-1  && j==-1){    //improve later: undo multiple times
                gameBoard.undo();
                gameBoard.undo();
                gameBoard.printBoard(player);
                cout << "undo done" << endl;
                cout << "Your turn (format: row col): ";
                cin >> i >> j;
            }

            while(!gameBoard.getvalidmove(player).count({i, j})){
                cout << "Invalid move. Try again: ";
                cin >> i >> j;
            }
            move = {i, j};
        }
        else{
            move = callAI(gameBoard, player);
        }
        gameBoard.place(move.first, move.second, player);
        int nextplayer = gameBoard.hasWinner(player);

        switch(nextplayer){
        	case 2:		cout << "Player 1 wins!" << endl; 	break;
        	case -2:	cout << "Player 2 wins!" << endl;	break;
        	case 0:		cout << "It's a draw!" << endl;		break;
        	default:	player = nextplayer;
        }
    }
  return 0;
}
