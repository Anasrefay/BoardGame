#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"

vector<vector<char>>winner(3,vector<char>(3,' ')) ;
vector<vector<int>>visitedcell(9,vector<int>(9,0)) ;

char sympol = 'O' ;


template <typename T>
class ultimateTicTacToeBoard:public Board<T> {
public:
    ultimateTicTacToeBoard ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool smaller_win(int x , int y) {
        for (int i = 0 ; i < 3 ; ++i) {
            // rows and columns
            if ((this->board[x+i][y]==this->board[x+i][y+1] && this->board[x+i][y]==this->board[x+i][y+2] && this->board[x+i][y]!=0)
                ||
                (this->board[x][y+i]==this->board[x+1][y+i] && this->board[x][y+i]==this->board[x+2][y+i] && this->board[x][y+i]!=0)
                ) {
                return true ;
            }
        }
        // diagonal
        if (this->board[x][y]==this->board[x+1][y+1]&& this->board[x][y]==this->board[x+2][y+2]&&this->board[x][y]==sympol
            ||
            this->board[x][y+2]==this->board[x+1][y+1]&& this->board[x][y+2]==this->board[x+2][y]&&this->board[x][y+2]==sympol
            ) {
            return true ;
        }
        return false ;
    }
};

template <typename T>
class ultimateTicTacToePlayer : public Player<T> {
public:
    ultimateTicTacToePlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class ultimateTicTacToeRandomPlayer : public RandomPlayer<T>{
public:
    ultimateTicTacToeRandomPlayer (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
ultimateTicTacToeBoard<T>::ultimateTicTacToeBoard() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool ultimateTicTacToeBoard<T>::update_board(int x, int y, T mark) {
    sympol = sympol == 'X' ? 'O' : 'X' ;
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0) && !visitedcell[x][y]) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            is_win();
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void ultimateTicTacToeBoard<T>::display_board() {
    cout << "  " ;
    for (int i = 0 ; i < 9 ; i++) {
        cout << " " << i << "  "  ;
        if ((i+1)%3==0)cout << " " ;
    }
    cout << endl;
    for (int i = 0 ; i < 9 ; ++i) {
        cout << i << " " ;
        for (int j = 0 ; j < 9 ; ++j) {
            cout << " " ;
            if (this->board[i][j])
                cout << this->board[i][j] ;
            else
                cout << " " ;
            cout << " " ;
            cout << "|" ;
            if ((j+1)%3==0)
                cout << "|" ;
        }
        cout << endl ;
        cout << "  " ;
        for (int k = 0 ; k < 39 ; ++k) {
            cout << "=" ;
        }
        cout << endl ;
        if ((i+1)%3==0) {
            cout << "  " ;
            for (int k = 0 ; k < 39 ; ++k)
                cout << "=" ;
            cout << endl ;
        }
    }
}

// Returns true if there is any winner
template <typename T>
bool ultimateTicTacToeBoard<T>::is_win() {
    for (int i = 0 ; i < 9 ; i+=3) {
        for (int j = 0 ; j < 9 ; j+=3) {
            if (winner[i/3][j/3]==' ') {
                if (smaller_win(i,j)) {
                    for (int k = i ; k < i+3 ; k++) {
                        for (int l = j ; l < j+3 ; l++) {
                            visitedcell[k][l] = 1 ;
                            this->board[k][l] = sympol ;
                        }
                    }
                    winner[i/3][j/3]= sympol ;
                }
            }
        }
    }
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((winner[i][0] == winner[i][1] && winner[i][1] == winner[i][2] && winner[i][0] != ' ') ||
            (winner[0][i] == winner[1][i] && winner[1][i] == winner[2][i] && winner[0][i] !=  ' ')) {
            return true;
        }
    }

    // Check diagonals
    if ((winner[0][0] == winner[1][1] && winner[1][1] == winner[2][2] && winner[0][0] != ' ') ||
        (winner[0][2] == winner[1][1] && winner[1][1] == winner[2][0] && winner[0][2] != ' ')) {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool ultimateTicTacToeBoard<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool ultimateTicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
ultimateTicTacToePlayer<T>::ultimateTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void ultimateTicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
ultimateTicTacToeRandomPlayer<T>::ultimateTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void ultimateTicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 8
    y = rand() % this->dimension;
}


#endif //_3X3X_O_H
