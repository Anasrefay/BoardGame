#include <iostream>
#include "BoardGame_Classes.h"
#include "Four_in_row.h"
#include "NumericalTicTacToe.h"
#include "FourInRowMinMax_Player.h"
#include "NumericalMinMaxPlayer.h"
#include "ultimateTicTacToeHeader.h"

using namespace std;

void FourInRowGame() {
    int choice;
    Player<char>* players[2];
    FourInRowBoard<char>* B = new FourInRowBoard<char>();
    string playerXName, player2Name;

    cout << "Welcome to Four In Row Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. AI Player\n";

    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new FourInRowPlayer<char>(playerXName, 'X');
        break;
        case 2:
            players[0] = new FourInRowRandom_Player<char>('X');
        break;
        case 3 :
            players[0] = new FourInRowMinMax_Player<char>('X') ;
            players[0]->setBoard(B);
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. AI Player\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new FourInRowPlayer<char>(player2Name, 'O');
        break;
        case 2:
            players[1] = new FourInRowRandom_Player<char>('O');
        break;
        case 3 :
            players[1] = new FourInRowMinMax_Player<char>('O') ;
            players[1]->setBoard(B);
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return ;
    }

    // Create the game manager and run the game
    GameManager<char> fourinrow(B, players);
    fourinrow.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void NumericalTicTacToeGame() {
    int choice;
    Player<int>* players[2];
    NumericalBoard<int>* B = new NumericalBoard<int>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Numerical Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. AI Player\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new NumericalPlayer<int>(playerXName, 1);
        break;
        case 2:
            players[0] = new NumericalRandom_Player<int>(1);
        break;
        case 3:
            // players[0] = new NumericalMinMax_Player<int>(1) ;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new NumericalPlayer<int>(player2Name,2);
        break;
        case 2:
            players[1] = new NumericalRandom_Player<int>(2);
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return ;
    }

    // Create the game manager and run the game
    GameManager<int> numericalTicTacToe(B, players);
    numericalTicTacToe.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void ultimateTicTacToe() {
    int choice;
    Player<char>* players[2];
    ultimateTicTacToeBoard<char>* B = new ultimateTicTacToeBoard<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new ultimateTicTacToePlayer<char>(playerXName, 'X');
        break;
        case 2:
            players[0] = new ultimateTicTacToeRandomPlayer<char>('X');
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new ultimateTicTacToePlayer<char>(player2Name, 'O');
        break;
        case 2:
            players[1] = new ultimateTicTacToeRandomPlayer<char>('O');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return ;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}

void mainMenu() {
    cout << string(50,'#') << endl;
    cout << "Board Games" << endl ;
    cout << string(50,'#') << endl;
    cout << "1 - pyramic TicTacToe .\n" ;
    cout << "2 - Four in Row .\n" ;
    cout << "3 - 5 x 5 TicTacToe .\n" ;
    cout << "4 - Word TicTacToe\n" ;
    cout << "5 - Numerical TicTacToe .\n" ;
    cout << "6 - Misere TicTacToe .\n" ;
    cout << "7 - 4 x $ TicTacToe .\n" ;
    cout << "8 - Ultimate TicTacToe. \n" ;
    int choice ;
    cin >> choice ;
    if (choice==1) {
        //
    }
    else if (choice==2) {
        FourInRowGame();
    }
    else if (choice==3) {
        //
    }
    else if (choice==4) {
        //
    }
    else if (choice==5) {
        NumericalTicTacToeGame();
    }
    else if (choice==6) {
        //
    }
    else if (choice==7) {
        //
    }
    else if (choice==8) {
        ultimateTicTacToe();
    }
    else if (choice==9) {
        cout << "Bye Bye ya user ya habibi. \n" ;
        return ;
    }
    else {
        cout << "Invalid choice. \n" ;
        return ;
    }
}


int main() {
    mainMenu() ;
    return 0;
}