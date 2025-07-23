#include "tic_tac_toe.h"
#include <algorithm>
#include <iostream>

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
    char humanSymbol{ askHumanSymbol() };
    char computerSymbol{ getOpponentSymbol(humanSymbol) };
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
        turnSymbol = getOpponentSymbol(turnSymbol);
    }

    announceWinner(getWinner(board), computerSymbol, humanSymbol);
}

void instructions() {
    std::cout << "\t\tWellcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
    std::cout << "\nMake your move known by entering a number, 0 - 8.";
    std::cout << "\nThe number corresponds to the desired board position, as illustrated:\n";
    std::cout << "\n0 | 1 | 2";
    std::cout << "\n---------";
    std::cout << "\n3 | 4 | 5";
    std::cout << "\n---------";
    std::cout << "\n6 | 7 | 8\n";
}

char askYesNo(std::string question) {
    char response;
    do {
        std::cout << question << " (y/n): ";
        std::cin >> response;
    } while (response != 'y' && response != 'n');
    return response;
}

int askNumber(std::string question, int high, int low = 0) {
    int response;
    do {
        std::cout << question << " (" << low << " - " << high << "): ";
        std::cin >> response;
    } while (response > high || response < low);
    return response;
}

char askHumanSymbol() {
    bool isFirst{ askYesNo("Do you require the first move?") == 'y' };
    if (isFirst) {
        std::cout << "\nThen take the first move. You will need it.\n";
        return X;
    }

    std::cout << "\nYour bravary will be your undoing... I will go first.\n";
    return O;
}

char getOpponentSymbol(char symbol) {
    if (symbol == X) {
        return O;
    }
    return X;
}

void displayBoard(const std::vector<char>& board) {
    std::cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    std::cout << "\n\t" << "---------";
    std::cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    std::cout << "\n\t" << "---------";
    std::cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8] << "\n";
}
