#ifndef _5X5AI_H
#define _5X5AI_H

#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm>

template <typename T>
class MinMax_5x5_Player : public Player<T> {
public:
    MinMax_5x5_Player(T symbol);
    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(bool isMaximizing);
    std::pair<int, int> getBestMove();
};

template <typename T>
MinMax_5x5_Player<T>::MinMax_5x5_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

template <typename T>
void MinMax_5x5_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
int MinMax_5x5_Player<T>::calculateMinMax(bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;  
    }
    else if (this->boardPtr->is_draw()) {
        return 0;  
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T currentSymbol = isMaximizing ? this->symbol : (this->symbol == 'X' ? 'O' : 'X');

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, currentSymbol)) {
                int value = calculateMinMax(!isMaximizing);
                this->boardPtr->update_board(i, j, 0);  

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                }
                else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

template <typename T>
std::pair<int, int> MinMax_5x5_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(false);
                this->boardPtr->update_board(i, j, 0);  

                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestMove = { i, j };
                }
            }
        }
    }

    return bestMove;
}

#endif
