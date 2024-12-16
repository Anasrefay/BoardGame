#ifndef _MISEREMINMAXPLAYER_H
#define _MISEREMINMAXPLAYER_H

#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm>
using namespace std;

template <typename T>
class Misere_MinMax_Player : public Player<T> {
public:
    Misere_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    int evaluateBoard(T s);
    std::pair<int, int> getBestMove();
};
template <typename T>
Misere_MinMax_Player<T>::Misere_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}
template <typename T>
void Misere_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}
template <typename T>
int Misere_MinMax_Player<T>::evaluateBoard(T s) {
    int score = 0;

    for (int i = 0; i < 3; ++i) {
        if (this->boardPtr->check_line({ {i, 0}, {i, 1}, {i, 2} }, s)) score += 1;
        if (this->boardPtr->check_line({ {0, i}, {1, i}, {2, i} }, s)) score += 1;
    }
    if (this->boardPtr->check_line({ {0, 0}, {1, 1}, {2, 2} }, s)) score += 1;
    if (this->boardPtr->check_line({ {0, 2}, {1, 1}, {2, 0} }, s)) score += 1;

    return score;
}
template <typename T>
int Misere_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -100 : 100; 
    }
    else if (this->boardPtr->is_draw()) {
        return 0; 
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int moveValue = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); 

                if (isMaximizing) {
                    bestValue = std::max(bestValue, moveValue);
                }
                else {
                    bestValue = std::min(bestValue, moveValue);
                }
            }
        }
    }

    return bestValue;
}

template <typename T>
std::pair<int, int> Misere_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int currentScore = -evaluateBoard(opponentSymbol); 
                this->boardPtr->update_board(i, j, 0); 

                if (currentScore > bestValue) {
                    bestValue = currentScore;
                    bestMove = { i, j };
                }
            }
        }
    }

    return bestMove;
}

#endif 
