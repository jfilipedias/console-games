#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

void guessMyNumber() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    int randNumber{ dist(mt) };
    int tries{ 0 };
    int guess{ 0 };

    std::cout << "\t\tGuess My Number\n";

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
