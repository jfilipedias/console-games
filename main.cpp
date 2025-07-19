#include "guess_my_number.h"
#include "word_jumble.h"
#include <iostream>

int main() {
    std::cout << "\t\tWellcome to Console Games!!!\n\n";

    bool quit{ false };
    while (!quit) {
        int choice{ 0 };
        std::cout << "Choose a game bellow to play:\n";
        std::cout << "(1) Guess My Number\n";
        std::cout << "(2) Word Jumble\n";
        std::cout << "Enter a number: ";
        std::cin >> choice;
        std::cout << "\n";

        if (choice == 1) {
            guessMyNumber();
        } else if (choice == 2) {
            wordJumble();
        } else {
            std::cout << "Invalid option!";
        }

        std::string input{ "" };
        std::cout << "\nEnter 'quit' to quit the program or any key to continue: ";
        std::cin >> input;
        std::cout << "\n";
        quit = input == "quit";
    }
}
