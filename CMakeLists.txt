cmake_minimum_required(VERSION 3.30)
project(c__)

set(CMAKE_CXX_STANDARD 23)

add_executable(c__ A2_S6_20230260_sheetpb5.cpp
        BoardGame_Classes.h
        Four_in_row.h
        ultimateTicTacToeHeader.h
        NumericalTicTacToe.h
        "../Assignment Demo/MinMaxPlayer.h"
        NumericalMinMaxPlayer.h
)
