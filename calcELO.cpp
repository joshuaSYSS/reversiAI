#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include "core/reversi.h"
#include "minimax.h"
using namespace std;

// Directions for checking valid moves (8 neighbors)
const int DR[] = {-1, -1, -1,  0,  0,  1, 1, 1};
const int DC[] = {-1,  0,  1, -1,  1, -1, 0, 1};

// ==========================================
// 1. HELPER: Check valid moves
// ==========================================
struct Move { int r, c; };

vector<Move> get_valid_moves(const vector<vector<int>>& board, int player) {
    vector<Move> moves;
    int opponent = -player;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (board[r][c] != 0) continue; // Must be empty

            for (int i = 0; i < 8; i++) {
                int nr = r + DR[i];
                int nc = c + DC[i];
                
                // Must be adjacent to opponent
                if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && board[nr][nc] == opponent) {
                    // Keep scanning in that direction
                    while (true) {
                        nr += DR[i];
                        nc += DC[i];
                        if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) break; // Out of bounds
                        if (board[nr][nc] == 0) break; // Found empty space
                        if (board[nr][nc] == player) {
                            // Found our own piece -> Valid sandwich
                            moves.push_back({r, c});
                            goto next_square; // Break out of direction loop to next board square
                        }
                    }
                }
            }
            next_square:;
        }
    }
    return moves;
}

// ==========================================
// 2. HELPER: Apply Move (Flip pieces)
// ==========================================
void apply_move(vector<vector<int>>& board, Move move, int player) {
    int r = move.r;
    int c = move.c;
    board[r][c] = player;
    int opponent = -player;

    for (int i = 0; i < 8; i++) {
        int nr = r + DR[i];
        int nc = c + DC[i];
        
        // Check if this direction has captures
        if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && board[nr][nc] == opponent) {
            int runner_r = nr;
            int runner_c = nc;
            while (true) {
                runner_r += DR[i];
                runner_c += DC[i];
                if (runner_r < 0 || runner_r >= 8 || runner_c < 0 || runner_c >= 8) break;
                if (board[runner_r][runner_c] == 0) break;
                if (board[runner_r][runner_c] == player) {
                    // Valid sandwich found, go back and flip
                    int flip_r = nr;
                    int flip_c = nc;
                    while (flip_r != runner_r || flip_c != runner_c) {
                        board[flip_r][flip_c] = player;
                        flip_r += DR[i];
                        flip_c += DC[i];
                    }
                    break;
                }
            }
        }
    }
}

// ==========================================
// 3. THE RANDOMIZER
// ==========================================
// Returns the player integer (1 or -1) who should play NEXT.
int randomize_board(vector<vector<int>>& board, int moves_to_play) {
    // Setup Random Number Generator
    static std::mt19937 rng(std::time(nullptr)); // Seeding with time

    int current_player = 1; // Player 1 starts
    
    for (int i = 0; i < moves_to_play; ++i) {
        vector<Move> valid_moves = get_valid_moves(board, current_player);

        if (valid_moves.empty()) {
            // If current player has no moves, check if opponent does
            current_player = -current_player;
            valid_moves = get_valid_moves(board, current_player);
            
            // If both have no moves, game is over (unlikely in opening)
            if (valid_moves.empty()) break; 
        }

        // Pick a random move
        std::uniform_int_distribution<int> dist(0, valid_moves.size() - 1);
        Move random_move = valid_moves[dist(rng)];

        // Execute
        apply_move(board, random_move, current_player);
        
        // Switch turn
        current_player = -current_player;
    }

    return current_player;
}

// ==========================================
// MAIN (Testing)
// ==========================================
void print_board(const vector<vector<int>>& b) {
    cout << "  0 1 2 3 4 5 6 7" << endl;
    for(int r=0; r<8; r++) {
        cout << r << " ";
        for(int c=0; c<8; c++) {
            char symbol = '.';
            if (b[r][c] == 1) symbol = 'B';       // Black
            if (b[r][c] == -1) symbol = 'W';      // White
            cout << symbol << " ";
        }
        cout << endl;
    }
}

//Greedy bot code
pair<int, int> greedyAI(Board& board, int player){
    auto validmove = board.getvalidmove(player);
    if(validmove.empty()) return {-1, -1};

    int maxFlips = -1;
    pair<int, int> bestMove = {-1, -1};

    for(auto [i, j] : validmove){
        Board tempBoard = board;
        tempBoard.place(i, j, player);
        int flipCount = 0;
        for(int x = 0; x < tempBoard.BOARD_SIZE; x++){
            for(int y = 0; y < tempBoard.BOARD_SIZE; y++){
                if(tempBoard.board[x][y] == player) flipCount++;
            }
        }

        if(flipCount > maxFlips){
            maxFlips = flipCount;
            bestMove = {i, j};
        }
    }
    return bestMove;
}

double calculate_expected_score(double my_rating, double opponent_rating) {
    // Formula: 1 / (1 + 10 ^ ((RatingB - RatingA) / 400))
    return 1.0 / (1.0 + std::pow(10.0, (opponent_rating - my_rating) / 400.0));
}

// 2. Calculate the new rating based on the match result
// actual_score: 1.0 = Win, 0.5 = Draw, 0.0 = Loss
double update_elo(double my_rating, double opponent_rating, double actual_score, int k_factor = 32) {
    double expected_score = calculate_expected_score(my_rating, opponent_rating);
    
    return my_rating + k_factor * (actual_score - expected_score);
}

void calc(){
    int t = 10;
    while(t--){
    int player = 1;
    vector<vector<int>> initial_board = {
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 1, -1, 0, 0, 0},
        { 0, 0, 0, -1, 1, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int next_player = randomize_board(initial_board, 8);
    Board gameBoard = Board(initial_board);
    gameBoard.refreshBoard();

    player = next_player;

    bool gamePlaying = true;
    double result = 0;
    while(gamePlaying){
        pair<int, int> move = {-1,-1};
        gameBoard.printBoard(player);

        if(player == -1){
            move = greedyAI(gameBoard, player);
            cout << "Greedy Bot plays: " << move.first << " " << move.second << endl;
        }
        else{
            move = callAI(gameBoard, player);
            if(move == pair{-1, -1}){
                result = 0.0;
                break;
            }
        }
        gameBoard.place(move.first, move.second, player);
        int nextplayer = gameBoard.hasWinner(player);

        switch(nextplayer){
        	case 2:		result = 1.0; 	gamePlaying = false; break;
        	case -2:	result = 0.0;	gamePlaying = false; break;
        	case 0:		result = 0.5;   gamePlaying = false; break;
        	default:	player = nextplayer;
        }
    }

    double my_elo = 1200.0;
    double enemy_elo = 800.0; // The Greedy Bot

    // Scenario: You played a game and WON (Score = 1.0)

    double new_elo = update_elo(my_elo, enemy_elo, result);

    std::cout << "Old Elo: " << my_elo << std::endl;
    std::cout << "New Elo: " << new_elo << std::endl;
    
    // Usually displayed as integer
    std::cout << "Display Elo: " << (int)std::round(new_elo) << std::endl;

    my_elo = new_elo;

    new_elo = update_elo(enemy_elo, my_elo, 1.0 - result); // Greedy bot's perspective
    enemy_elo = new_elo;
}
}