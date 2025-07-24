#pragma once
#include <string>
#include <vector>

void ticTacToe();

void instructions();

char askYesNo(std::string question);

int askNumber(std::string question, int high, int low = 0);

char askHumanSymbol();

char getOpponentSymbol(char symbol);

void displayBoard(const std::vector<char>* const board);

char getWinner(const std::vector<char>* const board);

bool isLegal(int move, const std::vector<char>* const board);

int humanMove(const std::vector<char>* const board, char humanSymbol);

int computerMove(std::vector<char> board, char computerSymbol);

void announceWinner(char winnerSymbol, char computerSymbol, char humanSymbol);
