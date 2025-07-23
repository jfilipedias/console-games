#include "tic_tac_toe.h"
#include <algorithm>
#include <iostream>

const char X_SYMBOL = 'X';
const char O_SYMBOL = 'O';
const char EMPTY_SYMBOL = ' ';
const char TIE_SYMBOL = 'T';
const char NO_ONE_SYMBOL = 'N';

void ticTacToe() {
    int position;
    const int NUM_SQUARES = 9;
    std::vector<char> board(NUM_SQUARES, EMPTY_SYMBOL);

    instructions();
    char humanSymbol{ askHumanSymbol() };
    char computerSymbol{ getOpponentSymbol(humanSymbol) };
    char turnSymbol{ X_SYMBOL };

    displayBoard(board);

    while (getWinner(board) == NO_ONE_SYMBOL) {
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

int askNumber(std::string question, int high, int low) {
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
        return X_SYMBOL;
    }

    std::cout << "\nYour bravary will be your undoing... I will go first.\n";
    return O_SYMBOL;
}

char getOpponentSymbol(char symbol) {
    if (symbol == X_SYMBOL) {
        return O_SYMBOL;
    }
    return X_SYMBOL;
}

void displayBoard(const std::vector<char>& board) {
    std::cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    std::cout << "\n\t" << "---------";
    std::cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    std::cout << "\n\t" << "---------";
    std::cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8] << "\n";
}

char getWinner(const std::vector<char>& board) {
    const int WINNING_COMBINATIONS[8][3]{ { 0, 1, 2 },
                                          { 3, 4, 5 },
                                          { 6, 7, 8 },
                                          { 0, 3, 6 },
                                          { 1, 4, 7 },
                                          { 2, 5, 8 },
                                          { 0, 4, 8 },
                                          { 2, 4, 6 } };

    const int TOTAL_COMBINATIONS{ 8 };
    for (int i{ 0 }; i < TOTAL_COMBINATIONS; ++i) {
        char symbol{ board[WINNING_COMBINATIONS[i][0]] };
        if (symbol != EMPTY_SYMBOL &&
            board[WINNING_COMBINATIONS[i][1]] == symbol &&
            board[WINNING_COMBINATIONS[i][2]] == symbol) {
            return symbol;
        }
    }

    if (count(board.begin(), board.end(), EMPTY_SYMBOL) == 0) {
        return TIE_SYMBOL;
    }

    return NO_ONE_SYMBOL;
}

inline bool isLegal(int move, const std::vector<char>& board) {
    return board[move] == EMPTY_SYMBOL;
}

int humanMove(const std::vector<char>& board, char humanSymbol) {
    int move{ askNumber("Where will you move?", board.size() - 1) };
    while (!isLegal(move, board)) {
        std::cout << "\nThat square is already accupied, foolish human.\n";
        move = askNumber("Where will you move?", board.size() - 1);
        std::cout << "Fine...\n";
    }
    return move;
}

int computerMove(std::vector<char> board, char computerSymbol) {
    unsigned int move{ 0 };
    bool found{ false };

    // If computer can win, make the move
    while (!found && move < board.size()) {
        if (isLegal(move, board)) {
            board[move] = computerSymbol;
            found = getWinner(board) == computerSymbol;
            board[move] = EMPTY_SYMBOL;
        }

        if (!found) {
            ++move;
        }
    }

    // If computer can block the human, make the move
    if (!found) {
        move = 0;
        char humanSymbol{ getOpponentSymbol(computerSymbol) };

        while (!found && move < board.size()) {
            if (isLegal(move, board)) {
                board[move] = humanSymbol;
                found = getWinner(board) == humanSymbol;
                board[move] = EMPTY_SYMBOL;
            }

            if (!found) {
                ++move;
            }
        }
    }

    // Make the best possible move
    if (!found) {
        move = 0;
        unsigned int i{ 0 };

        const int BEST_MOVES[9]{ 4, 0, 2, 6, 8, 1, 3, 5, 7 };
        while (!found && i < board.size()) {
            move = BEST_MOVES[i];
            if (isLegal(move, board)) {
                found = true;
            }

            ++i;
        }
    }

    std::cout << "I shall take square number " << move << ".";
    return move;
}

void announceWinner(char winnerSymbol, char computerSymbol, char humanSymbol) {
    if (winnerSymbol == computerSymbol) {
        std::cout << winnerSymbol << "'s won!";
        std::cout << "\nAs I predicted, human, I'm triumphant once more -- proof";
        std::cout << "\nthat computers are superior to humans in all regards.\n";
    } else if (winnerSymbol == humanSymbol) {
        std::cout << winnerSymbol << "'s won!";
        std::cout << "\nNo, no! It cannot be! Somehow you tricked me, human.";
        std::cout << "\nBut never again! I, the computer, so swear it!\n";
    } else {
        std::cout << "It's a tie.";
        std::cout << "\nYou were most lucky, human, and somehow managed to tie me.";
        std::cout << "\nCelebrate... for this is the you'll ever achive.\n";
    }
}
