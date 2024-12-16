#ifndef _5x5X_O_H
#define _5x5X_O_H
#define COLOR_X "\033[38;5;81m"
#define COLOR_O "\033[38;5;55m" 
#define RESET_COLOR "\033[0m"   
#define COLOR_GREEN "\033[1;32m"
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  
#include <vector>

using namespace std;

template <typename T>
class Board_5x5_XO : public Board<T> {
private:
    int scoreX;
    int scoreO;
    int rounds;
    int Pmoves;
    vector<vector<bool>> visited;

public:
    Board_5x5_XO();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int get_score(T symbol);
    void update_score(int x, int y, T symbol);
    void reset_game();
};

template <typename T>
class Player_5x5_XO : public Player<T> {
public:
    Player_5x5_XO(string name, T symbol);
    void getmove(int& x, int& y);
};
template <typename T>
class Random_5x5_Player : public RandomPlayer<T> {
public:
    Random_5x5_Player(T symbol);
    void getmove(int& x, int& y);
};
template <typename T>
Board_5x5_XO<T>::Board_5x5_XO() {
    this->rows = this->columns = 5;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    this->scoreX = 0;
    this->scoreO = 0;
    this->rounds = 0;
    this->Pmoves = 0;
    this->visited = vector<vector<bool>>(this->rows, vector<bool>(this->columns, false));
}

template <typename T>
bool Board_5x5_XO<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            update_score(x, y, mark);
            cout << "\n" << COLOR_GREEN << "Scores after this move" << RESET_COLOR << "\n";
            cout << "-------------------------" << endl;  
            cout << "Player " << COLOR_X << "X" << RESET_COLOR << ":" << scoreX << "    Player " << COLOR_O << "O" << RESET_COLOR << ":" << scoreO << endl;
        }
        return true;
    }
    return false;
}


template <typename T>
void Board_5x5_XO<T>::display_board() {
    cout << "\n  0   1   2   3   4\n";
    cout << "----------------------\n";

    for (int i = 0; i < this->rows; i++) {
        cout << i << " ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) {
                cout << "   ";
            }
            else {
                if (this->board[i][j] == 'X') {
                    cout << COLOR_X << " X " << RESET_COLOR;
                }
                else if (this->board[i][j] == 'O') {
                    cout << COLOR_O << " O " << RESET_COLOR;
                }
            }
            if (j != this->columns - 1) cout << "|";
        }
        cout << endl;

        if (i != this->rows - 1) {
            cout << "  ---+---+---+---+---\n";
        }
    }
    cout << endl;
}



template <typename T>
void Board_5x5_XO<T>::update_score(int x, int y, T symbol) {
    vector<pair<int, int>> v = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

    for (auto& c : v) {
        int count = 1;
        for (int k = 1; k < 3; k++) {
            int x2 = x + c.first * k;
            int y2 = y + c.second * k;
            if (x2 >= 0 && x2 < this->rows && y2 >= 0 && y2 < this->columns
                && this->board[x2][y2] == toupper(symbol)) {
                count++;
            }
            else {
                break;
            }
        }
        for (int k = 1; k < 3; k++) {
            int x2 = x - c.first * k;
            int y2 = y - c.second * k;
            if (x2 >= 0 && x2 < this->rows && y2 >= 0 && y2 < this->columns
                && this->board[x2][y2] == toupper(symbol)) {
                count++;
            }
            else {
                break;
            }
        }
        if (count == 3) {
            if (symbol == 'X') {
                this->scoreX++;
            }
            else if (symbol == 'O') {
                this->scoreO++;
            }
        }
    }
}

template <typename T>
int Board_5x5_XO<T>::get_score(T symbol) {
    return (symbol == 'X') ? scoreX : scoreO;
}

template <typename T>
bool Board_5x5_XO<T>::game_is_over() {
    return this->n_moves == 24;
}

template <typename T>
bool Board_5x5_XO<T>::is_win() {
    if (game_is_over()) {
        if (this->scoreX > this->scoreO) {
            return true;
        }
        else if (this->scoreX < this->scoreO) {
            return true;
        }
    }
    return false;
}

template <typename T>
void Board_5x5_XO<T>::reset_game() {
    this->n_moves = 0;
    this->scoreX = 0;
    this->scoreO = 0;
    this->visited = vector<vector<bool>>(this->rows, vector<bool>(this->columns, false));
    display_board();
}

template <typename T>
Player_5x5_XO<T>::Player_5x5_XO(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Player_5x5_XO<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
bool Board_5x5_XO<T>::is_draw() {
    return (this->n_moves == 24 && !is_win());
}
template <typename T>
Random_5x5_Player<T>::Random_5x5_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Random_5x5_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}






#endif
