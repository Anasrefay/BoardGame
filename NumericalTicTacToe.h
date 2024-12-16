#ifndef NUMERICALTICTACTOE_H
#define NUMERICALTICTACTOE_H


#include "BoardGame_Classes.h"

bool playerisAI[2] = {false,false} ;
int idx = 1 ;
vector<int>visitednumbers(10,0) ;

template <typename T>
class NumericalBoard:public Board<T> {
public:
    NumericalBoard ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class NumericalPlayer : public Player<T> {
public:
    NumericalPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class NumericalRandom_Player: public RandomPlayer<T>{
public:
    NumericalRandom_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
NumericalBoard<T>::NumericalBoard() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}


vector<int>vis(10) ;

template <typename T>
bool NumericalBoard<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
            idx = !idx ;
        }
        else {
            this->n_moves++;
            this->board[x][y] = mark;
            idx = !idx ;
        }
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void NumericalBoard<T>::display_board() {
    cout << "  " ;
    for (int i = 0 ; i < this->columns; i++)
        cout << "   " << i << "  ";
    for (int i = 0; i < this->rows; i++) {
        cout << "\n" << i << " |";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) {
                cout << "     ";
            }
            else {
                cout << "  " << this->board[i][j] << "  " ;
            }
            cout << "|" ;
        }
        cout << "\n   ------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool NumericalBoard<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 && this->board[i][2] && this->board[i][1] && this->board[i][0]) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15 && this->board[2][i] && this->board[1][i] && this->board[0][i])) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 && this->board[0][0] && this->board[1][1] && this->board[2][2]) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] && this->board[0][2] && this->board[1][1] && this->board[2][0])) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool NumericalBoard<T>::is_draw() {
    bool vis = false ;
    for (int i = 1 ; i <= 9 ; ++i) {
        if (!visitednumbers[i]) {
            vis = true ;
            break ;
        }
    }
    if (!vis)return true ;
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool NumericalBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
NumericalPlayer<T>::NumericalPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void NumericalPlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    vector<int>numbers ;
    if (idx) {
        cout << "choose a number from the list : \n" ;
        for (int i = 1 ; i <= 9 ; i += 2) {
            if (!visitednumbers[i]) {
                cout << i << " " ;
                numbers.push_back(i) ;
            }
        }
        cout << endl;
        int choice ;
        bool found = false ;
        while (!found){
            cin >> choice ;
            for (int i = 0 ; i < numbers.size(); ++i) {
                if (choice==numbers[i]) {
                    found = true ;
                    break ;
                }
            }
            if (!found)
                cout << "this number is not in your list\n" ;
        }
        NumericalPlayer<int>::symbol = choice ;
        visitednumbers[choice] = 1 ;
    }else {
        cout << "choose a number from the list : \n" ;
        for (int i = 2 ; i <= 9 ; i += 2) {
            if (!visitednumbers[i]) {
                cout << i << " " ;
                numbers.push_back(i) ;
            }
        }
        cout << endl;
        int choice ;
        bool found = false ;
        while (!found){
            cin >> choice ;
            for (int i = 0 ; i < numbers.size(); ++i) {
                if (choice==numbers[i]) {
                    found = true ;
                    break ;
                }
            }
            if (!found)
                cout << "this number is not in your list\n" ;
        }
        NumericalPlayer<int>::symbol = choice ;
        visitednumbers[choice] = 1 ;
    }
}

// Constructor for X_O_Random_Player
template <typename T>
NumericalRandom_Player<T>::NumericalRandom_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void NumericalRandom_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}


#endif //NUMERICALTICTACTOE_H
