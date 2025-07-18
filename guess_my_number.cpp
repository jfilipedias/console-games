#include "guess_my_number.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void guessMyNumber() {
    srand(static_cast<unsigned int>(time(0)));
    int randNumber{ rand() % 100 + 1 };
    int tries{ 0 };
    int guess{ 0 };

    std::cout << "Wellcome to Guess My Number!!!\n";

    while (randNumber != guess) {
        std::cout << "\nEnter a guess: ";
        std::cin >> guess;
        tries++;

        if (guess < randNumber) {
            std::cout << "Too low!\n";
        } else if (guess > randNumber) {
            std::cout << "Too high!\n";
        }
    }

    std::cout << "That's it. You got it in " << tries << " guesses";
}
