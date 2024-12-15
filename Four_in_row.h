#ifndef FOUR_IN_ROW_H
#define FOUR_IN_ROW_H

#include "BoardGame_Classes.h"

template <typename T>
class FourInRowBoard:public Board<T> {
public:
    vector<vector<int>> v ;
    FourInRowBoard ();
    vector<vector<int>> visitedFunc() {
        vector<vector<int>>visited(6,vector<int>(7));

        for (int i = 0 ; i < 7 ; ++i) {
            for (int j = 5 ; j >= 0 ; j--) {
                if (this->board[j][i]==' ') {
                    visited[j][i]=1;
                    break;
                }
            }
        }
        return visited ;
    }
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class FourInRowPlayer : public Player<T> {
public:
    FourInRowPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class FourInRowRandom_Player : public RandomPlayer<T>{
public:
    FourInRowRandom_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
FourInRowBoard<T>::FourInRowBoard() {
    this->rows = 6 ;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool FourInRowBoard<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' '|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = ' ';
        }
        else {
            if (v[x][y]) {
                this->n_moves++;
                this->board[x][y] = toupper(mark);
                return true;
            }
        }
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void FourInRowBoard<T>::display_board() {
    v = visitedFunc() ;
    cout << "  " ;
    for (int i = 0 ; i < this->columns; i++)
        cout << "  " << i << " ";
    for (int i = 0; i < this->rows; i++) {
        cout << "\n" << i << " |";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n  -----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool FourInRowBoard<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != ' ') {
                // Horizontal
                if (j <= this->columns - 4 &&
                    this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2] &&
                    this->board[i][j] == this->board[i][j + 3]) {
                    return true;
                    }
                // Vertical
                if (i <= this->rows - 4 &&
                    this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i][j] == this->board[i + 2][j] &&
                    this->board[i][j] == this->board[i + 3][j]) {
                    return true;
                    }
                // Diagonal (\ direction)
                if (i <= this->rows - 4 && j <= this->columns - 4 &&
                    this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i][j] == this->board[i + 2][j + 2] &&
                    this->board[i][j] == this->board[i + 3][j + 3]) {
                    return true;
                    }
                // Diagonal (/ direction)
                if (i <= this->rows - 4 && j >= 3 &&
                    this->board[i][j] == this->board[i + 1][j - 1] &&
                    this->board[i][j] == this->board[i + 2][j - 2] &&
                    this->board[i][j] == this->board[i + 3][j - 3]) {
                    return true;
                    }
            }
        }
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool FourInRowBoard<T>::is_draw() {
    return (this->n_moves == this->rows*this->columns && !is_win());
}

template <typename T>
bool FourInRowBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
FourInRowPlayer<T>::FourInRowPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FourInRowPlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x (0 to 5)and y (0 to 6) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
FourInRowRandom_Player<T>::FourInRowRandom_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 6;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void FourInRowRandom_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension+1;
}


#endif
