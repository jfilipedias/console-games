#pragma once
#include <string>
#include <vector>

void instructions();

char askYesNo(std::string question);

int askNumber(std::string question, int high, int low = 0);

char askHumanSymbol();

char getOpponentSymbol(char symbol);

void displayBoard(const std::vector<char>& board);

char getWinner(const std::vector<char>& board);

bool isLegal(const std::vector<char>& board);

int humanMove(const std::vector<char>& board, char humanSymbol);

int computerMove(std::vector<char>& board, char computerSymbol);

void announceWinner(char winnerSymbol, char computerSymbol, char humanSymbol);

void ticTacToe();
