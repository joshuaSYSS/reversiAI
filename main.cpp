#include <iostream>
#include "core/reversi.h"
#include "minimax.h"
#include "calcELO.h"
using namespace std;

bool count(const vector<pair<int, int>>& vec, const pair<int, int>& val){
    //Binary search
    auto it = lower_bound(vec.begin(), vec.end(), val);
    return it != vec.end() && *it == val;
}

int main(void){
    calc();

    int player = 1;
    Board gameBoard = Board();
    gameBoard.refreshBoard();

    bool gamePlaying = true;
    while(gamePlaying){
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

            while(!count(gameBoard.getvalidmove(player), {i, j})){
                cout << "Invalid move. Try again: ";
                cin >> i >> j;
            }
            move = {i, j};
        }
        else{
            move = callAI(gameBoard, player);
            if(move == pair{-1, -1}){
                cout << "AI gives up." << endl;
                cout << "You win!" << endl;
                break;
            }
        }
        gameBoard.place(move.first, move.second, player);
        int nextplayer = gameBoard.hasWinner(player);

        switch(nextplayer){
        	case 2:		cout << "Player 1 wins!" << endl; 	gamePlaying = false; break;
        	case -2:	cout << "Player 2 wins!" << endl;	gamePlaying = false; break;
        	case 0:		cout << "It's a draw!" << endl;		gamePlaying = false; break;
        	default:	player = nextplayer;
        }
    }
  return 0;
}
