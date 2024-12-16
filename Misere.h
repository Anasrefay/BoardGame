#ifndef MISERE_H
#define MISERE_H
#define COLOR_X "\033[38;5;81m"
#define COLOR_O "\033[38;5;55m" 
#define RESET_COLOR "\033[0m"   
#define COLOR_GREEN "\033[1;32m"
#include "BoardGame_Classes.h"

template <typename T>
class Misere_Board : public Board<T> {
private:
    T last_mark;

public:
    Misere_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    T get_last_mark() const { return last_mark; }
};

template <typename T>
class Misere_Player : public Player<T> {
public:
    Misere_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Misere_Random_Player : public RandomPlayer<T> {
public:
    Misere_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

template <typename T>
Misere_Board<T>::Misere_Board() {
    this->rows = this->columns = 3;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Misere_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            last_mark = mark;
        }
        return true;
    }
    return false;
}

template <typename T>
void Misere_Board<T>::display_board() {
    cout << "\n  0   1   2  \n";
    cout << "-------------- \n";

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
            cout << "  ---+---+---\n";
        }
    }
    cout << endl;
}

template <typename T>
bool Misere_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }
    return false;
}

template <typename T>
bool Misere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Misere_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------
template <typename T>
Misere_Player<T>::Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Misere_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
Misere_Random_Player<T>::Misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Misere_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif 
