#include <iostream>
#include "BoardGame_Classes.h"
#include "Four_in_row.h"
#include "NumericalTicTacToe.h"
#include "FourInRowMinMax_Player.h"
#include "NumericalMinMaxPlayer.h"
#include "ultimateTicTacToeHeader.h"
#include "4x4tictactoe.h"
#include "pyramic.h"
#include "pyramic_AI.h"
#include "Word_tictactoe.h"
#include "Word_tictactoe_AI.h"
#include "5x5X_O.h"
#include "5x5AI.h"
#include "Misere.h"
#include "MisereMinMaxPlayer.h"
using namespace std;

void MisereGame()
{
    int choice;
    Player<char>* players[2];
    Misere_Board<char>* B = new Misere_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Misere Game. :)\n";
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    


    switch (choice) {
    case 1:
        players[0] = new Misere_Player<char>(player2Name, 'X');
        break;
    case 2:
        players[0] = new Misere_Random_Player<char>('X');
        break;
    case 3:
        players[0] = new Misere_MinMax_Player<char>('X');
        players[0]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new Misere_Player<char>(playerXName, 'O');
        break;
    case 2:
        players[1] = new Misere_Random_Player<char>('O');
        break;
    case 3:
        players[1] = new Misere_MinMax_Player<char>('O');
        players[1]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}
void Game5x5()
{
    int choice;
    Player<char> *players[2];
    Board_5x5_XO<char> *B = new Board_5x5_XO<char>();
    string playerXName, playerOName;

    cout << "**********************************************\n";
    cout << "*      " << "Welcome to FCAI 5x5 Tic Tac Toe!\n";
    cout << "**********************************************\n\n";
    cout << "Player X Setup:\n";
    cout <<  "------------------------------------------------\n";
    cout << "Enter Player X name: ";
    cin >> playerXName;

    cout <<"\nChoose Player X type:\n";
    cout << "  [1] Human\n";
    cout << "  [2] Random Computer\n";
    cout << "  [3] AI Player\n";
    cout <<"Your choice: ";
    cin >> choice;

    while (choice < 1 || choice > 3)
    {
        cout <<"Invalid choice! Please enter 1, 2, or 3: ";
        cin >> choice;
    }

    if (choice == 1)
        players[0] = new Player_5x5_XO<char>(playerXName, 'X');
    else if (choice == 2)
        players[0] = new Random_5x5_Player<char>('X');
    else if (choice == 3)
        players[0] = new MinMax_5x5_Player<char>('X');

    cout <<"\n------------------------------------------------\n";

    cout <<"Player O Setup:\n";
    cout <<"------------------------------------------------\n"
    cout <<"Enter Player O name: " ;
    cin >> playerOName;

    cout << "\nChoose Player O type:\n";
    cout << "  [1] Human\n";
    cout << "  [2] Random Computer\n";
    cout << "  [3] AI Player\n";
    cout <<"Your choice: " ;
    cin >> choice;

    while (choice < 1 || choice > 3)
    {
        cout << "Invalid choice! Please enter 1, 2, or 3: " ;
        cin >> choice;
    }

    if (choice == 1)
        players[1] = new Player_5x5_XO<char>(playerOName, 'O');
    else if (choice == 2)
        players[1] = new Random_5x5_Player<char>('O');
    else if (choice == 3)
        players[1] = new MinMax_5x5_Player<char>('O');

    cout  << "\n------------------------------------------------\n";

    cout << "Great! Let the game begin. May the best player win!\n";
    cout << "------------------------------------------------\n\n";

    GameManager<char> game(B, players);
    game.run();

    delete B;
    for (int i = 0; i < 2; ++i)
        delete players[i];

    cout << "\nThank you for playing FCAI 5x5 Tic Tac Toe!\n";
    cout << "Goodbye and see you next time! :)\n";
}

void FourInRowGame()
{
    int choice;
    Player<char> *players[2];
    FourInRowBoard<char> *B = new FourInRowBoard<char>();
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

    switch (choice)
    {
    case 1:
        players[0] = new FourInRowPlayer<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new FourInRowRandom_Player<char>('X');
        break;
    case 3:
        players[0] = new FourInRowMinMax_Player<char>('X');
        players[0]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. AI Player\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new FourInRowPlayer<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new FourInRowRandom_Player<char>('O');
        break;
    case 3:
        players[1] = new FourInRowMinMax_Player<char>('O');
        players[1]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> fourinrow(B, players);
    fourinrow.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}

void NumericalTicTacToeGame()
{
    int choice;
    Player<int> *players[2];
    NumericalBoard<int> *B = new NumericalBoard<int>();
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

    switch (choice)
    {
    case 1:
        players[0] = new NumericalPlayer<int>(playerXName, 1);
        break;
    case 2:
        players[0] = new NumericalRandom_Player<int>(1);
        break;
    case 3:
        players[0] = new NumericalMinMax_Player<int>(1);
        players[0]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new NumericalPlayer<int>(player2Name, 2);
        break;
    case 2:
        players[1] = new NumericalRandom_Player<int>(2);
        break;
    case 3:
        players[1] = new NumericalMinMax_Player<int>(1);
        players[1]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<int> numericalTicTacToe(B, players);
    numericalTicTacToe.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}

void ultimateTicTacToe()
{
    int choice;
    Player<char> *players[2];
    ultimateTicTacToeBoard<char> *B = new ultimateTicTacToeBoard<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new ultimateTicTacToePlayer<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new ultimateTicTacToeRandomPlayer<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new ultimateTicTacToePlayer<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new ultimateTicTacToeRandomPlayer<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}

void PyramicTicTacToe()
{

    int choice;
    Player<char> *players[2];
    Board<char> *B = new Pyramic();
    string playerXName, player2Name;
    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        players[0] = new pyramic_player(playerXName, 'X');
        break;
    case 2:
        players[0] = new pyramic_Random('X');
        break;
    case 3:
        players[0] = new pyramic_AI('X');
        players[0]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        players[1] = new pyramic_player(player2Name, 'O');
        break;
    case 2:
        players[1] = new pyramic_Random('O');
        break;
    case 3:
        players[1] = new pyramic_AI('O');
        players[1]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }

    return;
}

void _4x4_TicTacToe()
{

    int choice;
    Player<char> *players[2];
    Board<char> *B = new _4x4tictactoe();
    string playerXName, player2Name;
    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        players[0] = new _4x4tictactoe_player(playerXName, 'X');
        break;
    case 2:
        players[0] = new _4x4tictactoe_Random('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        players[1] = new _4x4tictactoe_player(player2Name, 'O');
        break;
    case 2:
        players[1] = new _4x4tictactoe_Random('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    return;
}

void Wordtictactoe()
{

    int choice;
    Player<char> *players[2];
    Board<char> *B = new Word_tictactoe();
    string playerXName, player2Name;
    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        players[0] = new Word_tictactoe_player(playerXName, 'X');
        break;
    case 2:
        players[0] = new Word_tictactoe_Random('X');
        break;
    case 3:
        players[0] = new Word_tictactoe_AI('X');
        players[0]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        players[1] = new Word_tictactoe_player(player2Name, 'O');
        break;
    case 2:
        players[1] = new Word_tictactoe_Random('O');
        break;
    case 3:
        players[1] = new Word_tictactoe_AI('O');
        players[1]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }

    return;
}

void mainMenu()
{
    cout << string(50, '#') << endl;
    cout << "                   Board Games" << endl;
    cout << string(50, '#') << endl;
    cout << "1 - pyramic TicTacToe .\n";
    cout << "2 - Four in Row .\n";
    cout << "3 - 5 x 5 TicTacToe .\n";
    cout << "4 - Word TicTacToe\n";
    cout << "5 - Numerical TicTacToe .\n";
    cout << "6 - Misere TicTacToe .\n";
    cout << "7 - 4 x 4 TicTacToe .\n";
    cout << "8 - Ultimate TicTacToe. \n";
    cout << "9 - Exit. \n";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        PyramicTicTacToe() ;
    }
    else if (choice == 2)
    {
        FourInRowGame();
    }
    else if (choice == 3)
    {
        Game5x5();
    }
    else if (choice == 4)
    {
        Wordtictactoe();
    }
    else if (choice == 5)
    {
        NumericalTicTacToeGame();
    }
    else if (choice == 6)
    {
        MisereGame();
    }
    else if (choice == 7)
    {
        _4x4_TicTacToe();
    }
    else if (choice == 8)
    {
        ultimateTicTacToe();
    }
    else if (choice == 9)
    {
        cout << "Bye Bye ya user ya habibi. \n";
        return;
    }
    else
    {
        cout << "Invalid choice. \n";
        return;
    }
}

int main()
{
    mainMenu();
    return 0;
}
