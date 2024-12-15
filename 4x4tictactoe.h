#ifndef _4x4tictactoe_H_

#define _4x4tictactoe_H_

#include "BoardGame_Classes.h"

#include <bits/stdc++.h>


class _4x4tictactoe : public Board<char> {
public:
    _4x4tictactoe();
    bool update_board(int x, int y, char symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

_4x4tictactoe::_4x4tictactoe(){
    this->rows = 4;
    this->board = new char*[this->rows];
    for(int i=0;i<this->rows;i++){
        this->board[i] = new char[4];
        for(int j=0;j<4;j++){
            this->board[i][j] = ' ';
        }
    }
    for(int i=0;i<this->rows;i++){
            if(i%2 == 0){
                this->board[0][i] = 'O';
                this->board[3][i] = 'X';
            }
            else{
                this->board[0][i] = 'X';
                this->board[3][i] = 'O';
            }
        }
}



bool _4x4tictactoe::is_win() {
    vector<pair<int,int>>pos = {
        {0,0},{0,1},{0,2},{0,1},{0,2},{0,3},
        {1,0},{1,1},{1,2},{1,1},{1,2},{1,3},
        {2,0},{2,1},{2,2},{2,1},{2,2},{2,3},
        {3,0},{3,1},{3,2},{3,1},{3,2},{3,3},
        {0,0},{1,0},{2,0},{1,0},{2,0},{3,0},
        {0,0},{1,0},{2,0},{1,0},{2,0},{3,0},
        {0,1},{1,1},{2,1},{1,1},{2,1},{3,1},
        {0,2},{1,2},{2,2},{1,2},{2,2},{3,2},
        {0,3},{1,3},{2,3},{1,3},{2,3},{3,3},
        {1,0},{2,1},{3,2},{0,1},{1,2},{2,3},
        {2,0},{1,1},{0,2},{3,1},{2,2},{1,3},
        {0,0},{1,1},{2,2},{1,1},{2,2},{3,3}
    };
    for (int i = 0; i < pos.size(); i+=3)
    {
        if(board[pos[i].first][pos[i].second] == board[pos[i+1].first][pos[i+1].second] && board[pos[i+1].first][pos[i+1].second] == board[pos[i+2].first][pos[i+2].second] && board[pos[i].first][pos[i].second] != ' '){
            return true;
        }
    }
    return false;
}

bool _4x4tictactoe::is_draw(){
    return (n_moves == 16 && !is_win());
}


bool _4x4tictactoe::game_is_over(){
    return is_win();
}

int a,b;
bool flag = false;
bool _4x4tictactoe::update_board(int x, int y, char mark){
    if(flag){
        for (int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++){
                if(this->board[i][j] == mark){

                    if((min(i+1,3) == x && j == y && board[x][y] == ' ') || (i == x && min(j+1,3) == y && board[x][y] == ' ') || (max(i-1,0) == x && j == y && board[x][y] == ' ') || (i == x && max(j-1,0) == y && board[x][y] == ' ')){
                        this->board[x][y] = mark;
                        this->board[i][j] = ' ';
                        flag = false;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    else if(board[x][y] == ' ' && board[a][b] == mark){        
        if(min(a+1,3) == x && b == y || a == x && min(b+1,3) == y || max(a-1,0) == x && b == y || a == x && max(b-1,0) == y){
            this->board[x][y] = mark;          
            this->board[a][b] = ' ';
            return true;
        }
        else {
            return false;
        }
    }    
    return false;
}


void _4x4tictactoe::display_board(){
    cout<<"       0    "<<"1    "<<"2    "<<"3     "<<"\n\n";
    for (int i = 0; i < 4; i++)
    {       
        cout<<i<<"  ";
        cout << " | ";
        for (int j = 0; j < 4; j++)
        {
            cout<<setw(2)<<board[i][j]<<" | ";
        }
        cout<<"\n    ---------------------\n";
    }
}

class _4x4tictactoe_player : public Player<char> {
public:
    void getmove(int &x, int &y);
    char getsymbol();
    _4x4tictactoe_player(string name, char symbol);
    void setBoard(Board<char>* b);
};

_4x4tictactoe_player::_4x4tictactoe_player(string name, char symbol) : Player<char>(name,symbol) {};

void _4x4tictactoe_player::getmove(int &x, int &y){
    cout<<"(Player "<<symbol<<" turn) "<<"Enter a token: ";
    cin>>a>>b;
    cout<<"\nPlease enter your move x and y separated by spaces: ";
    cin>>x>>y;
}


char _4x4tictactoe_player::getsymbol(){
    return this->symbol;
}

void _4x4tictactoe_player::setBoard(Board<char>* b){
    this->boardPtr = b;
}


class _4x4tictactoe_Random : public _4x4tictactoe_player {
public:
    void getmove(int &x, int &y);
    _4x4tictactoe_Random(char symbol);
};

_4x4tictactoe_Random::_4x4tictactoe_Random(char symbol) : _4x4tictactoe_player("Random",symbol) {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
};

void _4x4tictactoe_Random::getmove(int &x, int &y){
    x = rand() % 4;  // Random number between 0 and 2
    y = rand() % 4;
    flag = true;
}



#endif

