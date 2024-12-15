#ifndef _PYRAMIC_H_
#define _PYRAMIC_H_

#include "BoardGame_Classes.h"

#include <bits/stdc++.h>

class Pyramic : public Board<char> {
public:
    Pyramic();
    bool update_board(int x, int y, char symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};



Pyramic::Pyramic(){
    this->rows = 3;
    this->board = new char*[this->rows];
    for(int i=0;i<this->rows;i++){
        this->board[i] = new char[2*i+1];
        for(int j=0;j<2*i+1;j++){
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}



bool Pyramic::is_win() {
    vector<pair<int,int>>pos = {
        {0,0},{1,0},{2,0},
        {0,0},{1,1},{2,2},
        {0,0},{1,2},{2,4},
        {1,0},{1,1},{1,2},
        {2,0},{2,1},{2,2},
        {2,1},{2,2},{2,3},
        {2,2},{2,3},{2,4},
    };
    for (int i = 0; i < pos.size(); i+=3)
    {
        if(board[pos[i].first][pos[i].second] == board[pos[i+1].first][pos[i+1].second] && board[pos[i+1].first][pos[i+1].second] == board[pos[i+2].first][pos[i+2].second] && board[pos[i].first][pos[i].second] != ' '){
            return true;
        }
    }
    
    return false;
}

bool Pyramic::is_draw(){
    return (n_moves == 9 && !is_win());
}


bool Pyramic::game_is_over(){
    return is_win() || is_draw();
}


bool Pyramic::update_board(int x, int y, char mark){
    if(mark == 0){
        this->n_moves--;
        this->board[x][y] = ' ';
        return true;
    }
    else{
        if((x == 0 && y == 0) || (x == 1 && y >=0 && y <= 2) || (x == 2 && y >= 0 && y <= 4)){   
            if(this->board[x][y] == ' '){
                this->n_moves++;
                this->board[x][y] = toupper(mark);
                return true;
            }
            else return false;
        }
        else return false;
    }
}
void Pyramic::display_board(){
    for (int i = 0; i < 3; i++)
    {       
        if(i == 0){
            cout<<"                    ";
        }
        if(i == 1){
            cout<<"          ";
        }
        cout<<"| ";
        for (int j = 0; j < 2*i+1; j++)
        {
            
            cout<<"("<<i<<","<<j<<")"<<setw(2)<<board[i][j]<<" | ";
            
        }
        cout<<"\n----------------------------------------------------\n";
    }
}

class pyramic_player : public Player<char> {
public:
    void getmove(int &x, int &y);
    char getsymbol();
    pyramic_player(string name, char symbol);
    void setBoard(Board<char>* b);
};

pyramic_player::pyramic_player(string name, char symbol) : Player<char>(name,symbol) {};

void pyramic_player::getmove(int &x, int &y){
    cout<<"\nPlease enter your move x and y separated by spaces: ";
    cin>>x>>y;
}


char pyramic_player::getsymbol(){
    return this->symbol;
}

void pyramic_player::setBoard(Board<char>* b){
    this->boardPtr = b;
}


class pyramic_Random : public pyramic_player {
public:
    void getmove(int &x, int &y);
    pyramic_Random(char symbol);
};

pyramic_Random::pyramic_Random(char symbol) : pyramic_player("Random",symbol) {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
};

void pyramic_Random::getmove(int &x, int &y){
    x = rand() % 3;  // Random number between 0 and 2
    y = rand() % 3;
}

#endif

