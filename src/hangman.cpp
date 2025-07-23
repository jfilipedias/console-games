#include "hangman.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

void hangman() {
    const int MAX_WRONG_GUESSES{ 8 };

    std::vector<std::string> words;
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");

    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::shuffle(words.begin(), words.end(), gen);

    const std::string THE_WORD{ words[0] };
    int wrongGuesses{ 0 };
    std::string lettersGuessed(THE_WORD.size(), '_');
    std::string triedLetters{ "" };

    std::cout << "\t\tHangman\n";

    while (wrongGuesses < MAX_WRONG_GUESSES && lettersGuessed != THE_WORD) {
        std::cout << "\nYou have " << wrongGuesses << " incorrect guesses";
        std::cout << "\nYou've used the following letters: " << triedLetters;
        std::cout << "\nSo far, the word is: " << lettersGuessed;

        char guess;
        std::cout << "\n\nEnter yout guess: ";
        std::cin >> guess;
        guess = std::toupper(guess);

        while (triedLetters.find(guess) != std::string::npos) {
            std::cout << "\nYou've already guessed " << guess;
            std::cout << "\n\nEnter yout guess: ";
            std::cin >> guess;
            guess = std::toupper(guess);
        }

        triedLetters += guess;

        if (THE_WORD.find(guess) != std::string::npos) {
            std::cout << "\nThat's right! " << guess << " is in the word.\n";

            for (int i{ 0 }; i < THE_WORD.length(); ++i) {
                if (THE_WORD[i] == guess) {
                    lettersGuessed[i] = guess;
                }
            }
        } else {
            std::cout << "\nSorry, " << guess << " isn't in the word.\n";
            ++wrongGuesses;
        }
    }

    if (wrongGuesses == MAX_WRONG_GUESSES) {
        std::cout << "\nYou've been hanged!";
    } else {
        std::cout << "\nYou guessed it!";
    }

    std::cout << "\nThe word was " << THE_WORD;
}
