#ifndef _WORD_TICTACTOE_AI_H
#define _WORD_TICTACTOE_AI_H

#include "BoardGame_Classes.h"
template <typename T>
class Word_tictactoe_AI : public Player<T> {
public:
    Word_tictactoe_AI(T symbol);

    void getmove(int& x, int& y) override;

private:
    std::pair<int, int> getBestMove();
};

//--------------------------------------- IMPLEMENTATION

#include <limits>
#include <algorithm> // For std::max and std::min
using namespace std;
// Constructor for the templated class
template <typename T>
Word_tictactoe_AI<T>::Word_tictactoe_AI(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void Word_tictactoe_AI<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}


// Find the best move using the minimax algorithm
template <typename T>
std::pair<int, int> Word_tictactoe_AI<T>::getBestMove() {

    // First, check if we can win in the next move

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (char k = 'A'; k <= 'Z'; ++k) {
                if (this->boardPtr->update_board(i, j, k)) {
                    if (this->boardPtr->is_win()) {
                        this->boardPtr->update_board(i, j, 0); // Undo move
                        this->symbol = toupper(k);
                        return {i, j}; // Win in next move
                    }
                    this->boardPtr->update_board(i, j, 0); // Undo move
                }
            }
        }
    }

    // If no immediate win or block, use MinMax to find the best move
    srand(static_cast<unsigned int>(time(0)));
    char c = rand() % 25 + 'A';
    this->symbol = toupper(c);
    int a = rand() % 3;
    int b = rand() % 3;   
    return {b,a};
}

#endif 