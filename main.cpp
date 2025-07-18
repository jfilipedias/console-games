#include "guess_my_number.h"
#include <iostream>

int main() {
    int choice{ 0 };

    std::cout << "Choose a game bellow to play:\n";
    std::cout << "(1) Guess my number\n";
    std::cout << "Enter a number: ";
    std::cin >> choice;
    std::cout << "\n";

    if (choice == 1) {
        guessMyNumber();
    } else {
        std::cout << "Invalid option!";
    }
}
