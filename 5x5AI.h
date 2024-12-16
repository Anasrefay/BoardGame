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
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
    int get_score(int row, int col, T symbol);
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
int MinMax_5x5_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    }
    else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int moveScore = get_score(i, j, s);
                int value = calculateMinMax(opponentSymbol, !isMaximizing) + moveScore;
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
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0);
                    return { i, j };
                }
                this->boardPtr->update_board(i, j, 0);
            }
        }
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0);
                    return { i, j };
                }
                this->boardPtr->update_board(i, j, 0);
            }
        }
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveScore = get_score(i, j, this->symbol);
                int moveValue = calculateMinMax(this->symbol, false) + moveScore;
                this->boardPtr->update_board(i, j, 0);

                if (moveValue > bestValue) {
                    bestMove = { i, j };
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

template <typename T>
int MinMax_5x5_Player<T>::get_score(int row, int col, T symbol) {
    int score = 0;

    auto evaluate_direction = [&](int dx, int dy) {
        int count = 0;
        for (int step = 1; step <= 4; ++step) {
            int newRow = row + step * dx;
            int newCol = col + step * dy;

            if (newRow < 0 || newRow >= 5 || newCol < 0 || newCol >= 5)
                break;

            if (this->boardPtr->get_value(newRow, newCol) == symbol) {
                count++;
            }
            else {
                break;
            }
        }
        return count;
        };

    score += evaluate_direction(0, 1);
    score += evaluate_direction(1, 0);
    score += evaluate_direction(1, 1);
    score += evaluate_direction(1, -1);

    return score;
}

#endif
