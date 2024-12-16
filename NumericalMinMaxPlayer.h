
#ifndef _aMINMAXPLAYER_H
#define _aMINMAXPLAYER_H

#include "BoardGame_Classes.h"
#include "NumericalTicTacToe.h"


template <typename T>
class NumericalMinMax_Player : public Player<T> {
public:
    NumericalMinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
};







//--------------------------------------- IMPLEMENTATION

#include <limits>
#include <algorithm> // For std::max and std::min
using namespace std;
// Constructor for the templated class
template <typename T>
NumericalMinMax_Player<T>::NumericalMinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void NumericalMinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
template <typename T>
int NumericalMinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (idx){
                for (int k = 1 ; k <= 9 ; k += 2){
                    if (!visitednumbers[k] && this->boardPtr->update_board(i, j, k)) {
                        visitednumbers[k]=1 ;
                        int value = calculateMinMax(opponentSymbol, !isMaximizing);
                        this->boardPtr->update_board(i, j, 0); // Undo move
                        visitednumbers[k]=0;


                        if (isMaximizing) {
                            bestValue = std::max(bestValue, value);
                        } else {
                            bestValue = std::min(bestValue, value);
                        }
                    }
                }
            }
            else {
                for (int k = 2 ; k <= 9 ; k += 2){
                    if (!visitednumbers[k] && this->boardPtr->update_board(i, j, k)) {
                        visitednumbers[k]=1 ;
                        int value = calculateMinMax(opponentSymbol, !isMaximizing);
                        this->boardPtr->update_board(i, j, 0); // Undo move
                        visitednumbers[k]=0 ;

                        if (isMaximizing) {
                            bestValue = std::max(bestValue, value);
                        } else {
                            bestValue = std::min(bestValue, value);
                        }
                    }
                }
            }
        }
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
template <typename T>
std::pair<int, int> NumericalMinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    // First, check if we can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (idx){
                for (int k = 2 ; k <= 9 ; k += 2){
                    if (!visitednumbers[k] && this->boardPtr->update_board(i, j, k)) {
                        if (this->boardPtr->is_win()) {
                            this->boardPtr->update_board(i, j, 0); // Undo move
                            return {i, j}; // Winning move found
                        }
                        this->boardPtr->update_board(i, j, 0); // Undo move
                    }
                }
            }
            else {
                for (int k = 1 ; k <= 9 ; k += 2){
                    if (!visitednumbers[k] && this->boardPtr->update_board(i, j, k)) {
                        if (this->boardPtr->is_win()) {
                            this->boardPtr->update_board(i, j, 0); // Undo move
                            return {i, j}; // Winning move found
                        }
                        this->boardPtr->update_board(i, j, 0); // Undo move
                    }
                }
            }
        }
    }

    idx = !idx ;
    // Second, check if the opponent can win in their next move and block them
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (idx){
                for (int k = 2 ; k <= 9 ; k+=2){
                    if (this->boardPtr->update_board(i, j, k)) {
                        if (this->boardPtr->is_win()) {
                            this->boardPtr->update_board(i, j, 0); // Undo move
                            return {i, j}; // Block opponent's winning move
                        }
                        this->boardPtr->update_board(i, j, 0); // Undo move
                    }
                }
            }
            else {
                for (int k = 1 ; k <= 9 ; k+=2){
                    if (this->boardPtr->update_board(i, j, k)) {
                        if (this->boardPtr->is_win()) {
                            this->boardPtr->update_board(i, j, 0); // Undo move
                            return {i, j}; // Block opponent's winning move
                        }
                        this->boardPtr->update_board(i, j, 0); // Undo move
                    }
                }
            }
        }
    }
    idx = !idx ;
    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (idx){
                for (int k = 2 ; k <= 9 ; k += 2 ){
                    if (this->boardPtr->update_board(i, j, k)) {
                        int moveValue = calculateMinMax(k, false);
                        this->boardPtr->update_board(i, j, 0); // Undo move

                        if (moveValue > bestValue) {
                            bestMove = {i, j};
                            bestValue = moveValue;
                        }
                    }
                }
            }
            else {
                for (int k = 1 ; k <= 9 ; k += 2 ){
                    if (this->boardPtr->update_board(i, j, k)) {
                        int moveValue = calculateMinMax(k, false);
                        this->boardPtr->update_board(i, j, 0); // Undo move

                        if (moveValue > bestValue) {
                            bestMove = {i, j};
                            bestValue = moveValue;
                        }
                    }
                }
            }
        }
    }

    return bestMove;
}
















#endif //_aMINMAXPLAYER_H
