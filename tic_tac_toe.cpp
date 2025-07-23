#include "tic_tac_toe.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void ticTacToe() {
    int position;
    const int NUM_SQUARES = 9;
    std::vector<char> board(NUM_SQUARES, EMPTY);

    instructions();
    char humanSymbol{ humanPiece() };
    char computerSymbol{ opponent(humanSymbol) };
    char turnSymbol{ X };

    displayBoard(board);

    while (getWinner(board) == NO_ONE) {
        if (turnSymbol == humanSymbol) {
            position = humanMove(board, humanSymbol);
            board[position] = humanSymbol;
        } else {
            position = computerMove(board, computerSymbol);
            board[position] = computerSymbol;
        }

        displayBoard(board);
        turnSymbol = opponent(turnSymbol);
    }

    announceWinner(getWinner(board), computerSymbol, humanSymbol);
}
