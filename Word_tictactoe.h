
#ifndef _tictactoe_H_

#define _tictactoe_H_

#include "BoardGame_Classes.h"

#include <bits/stdc++.h>

class Word_tictactoe : public Board<char>
{
public:
    Word_tictactoe();
    bool update_board(int x, int y, char symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

Word_tictactoe::Word_tictactoe()
{
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

bool Word_tictactoe::is_win()
{
    ifstream file("dic.txt");
    vector<pair<int, int>> pos = {
        {0, 0}, {0, 1}, {0, 2},
        {1, 0}, {1, 1}, {1, 2}, 
        {2, 0}, {2, 1}, {2, 2}, 
        {0, 0}, {1, 0}, {2, 0}, 
        {0, 1}, {1, 1}, {2, 1}, 
        {0, 2}, {1, 2}, {2, 2}, 
        {2, 0}, {1, 1}, {0, 2}, 
        {0, 0}, {1, 1}, {2, 2}
    };
    while (!file.eof())
    {
        string s;
        file >> s;
        for (int i = 0; i < pos.size(); i += 3)
        {
            string comp = "";
            comp += board[pos[i].first][pos[i].second];
            comp += board[pos[i + 1].first][pos[i + 1].second];
            comp += board[pos[i + 2].first][pos[i + 2].second];
            if (comp == s)
            {
                return true;
            }
            reverse(comp.begin(), comp.end());
            if (comp == s)
            {
                return true;
            }
        }
    }
    return false;
}

bool Word_tictactoe::is_draw()
{
    return (n_moves == 9 && !is_win());
}

bool Word_tictactoe::game_is_over()
{
    return is_win() || is_draw();
}

bool Word_tictactoe::update_board(int x, int y, char mark)
{
    if(mark == 0) {
        this->n_moves--;
        this->board[x][y] = ' ';
        return true;

    }
    else{
        if ((x >= 0 && x <= 2 && y >= 0 && y <= 2) && board[x][y] == ' ')
        {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            return true;
        }
        return false;
    }
    
}

void Word_tictactoe::display_board()
{
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

class Word_tictactoe_player : public Player<char>
{
public:
    void getmove(int &x, int &y);
    char getsymbol();
    Word_tictactoe_player(string name, char symbol);
    void setBoard(Board<char> *b);
};

Word_tictactoe_player::Word_tictactoe_player(string name, char symbol) : Player<char>(name, symbol) {};

void Word_tictactoe_player::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    char c;
    cout << "Please enter a symbol: ";
    cin >> c;
    symbol = toupper(c);
}

char Word_tictactoe_player::getsymbol()
{
    return this->symbol;
}

void Word_tictactoe_player::setBoard(Board<char> *b)
{
    this->boardPtr = b;
}

class Word_tictactoe_Random : public Word_tictactoe_player
{
public:
    void getmove(int &x, int &y);
    Word_tictactoe_Random(char symbol);
};

Word_tictactoe_Random::Word_tictactoe_Random(char symbol) : Word_tictactoe_player("Random", symbol)
{
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
};

void Word_tictactoe_Random::getmove(int &x, int &y)
{
    x = rand() % 3; // Random number between 0 and 2
    y = rand() % 3;
    char c = rand() % 25 + 'A';
    symbol = toupper(c);
}

#endif
