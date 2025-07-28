#include "critter_caretaker.h"
#include "game_lobby.h"
#include "guess_my_number.h"
#include "hangman.h"
#include "tic_tac_toe.h"
#include "word_jumble.h"
#include <iostream>

int main() {
    std::cout << "\t\tWellcome to Console Games!!!\n\n";

    int choice;
    do {
        std::cout << "Choose a game bellow to play:\n";
        std::cout << "0 - Exit the program\n";
        std::cout << "1 - Guess My Number\n";
        std::cout << "2 - Word Jumble\n";
        std::cout << "3 - Hangman\n";
        std::cout << "4 - Tic Tac Toe\n";
        std::cout << "5 - Critter Caretaker\n";
        std::cout << "6 - Game Lobby\n";
        std::cout << "Enter a number: ";
        std::cin >> choice;
        std::cout << "\n";

        if (choice == 0) {
            std::cout << "Good bye!";
        } else if (choice == 1) {
            guessMyNumber();
        } else if (choice == 2) {
            wordJumble();
        } else if (choice == 3) {
            hangman();
        } else if (choice == 4) {
            ticTacToe();
        } else if (choice == 5) {
            critterCaretaker();
        } else if (choice == 6) {
            gameLobby();
        } else {
            std::cout << "Invalid option!";
        }
    } while (choice != 0);
}
