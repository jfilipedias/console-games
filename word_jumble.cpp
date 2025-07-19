#include "word_jumble.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

void wordJumble() {
    enum fields { WORD,
                  HINT };

    const int NUM_WORDS{ 5 };
    const int NUM_FIELD{ 2 };
    const std::string WORDS[NUM_WORDS][NUM_FIELD]{
        { "wall", "Do you fell you're banging your head against something?" },
        { "glasses", "These might help you see the answer." },
        { "labored", "Going slowly, is it?" },
        { "persistence", "Keep at it." },
        { "jumble", "It's what the game is all about." }
    };

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    int choice{ dist(mt) % NUM_WORDS };
    std::string theWord{ WORDS[choice][WORD] };
    std::string theHint{ WORDS[choice][HINT] };

    std::string jumble{ theWord };
    int length{ static_cast<int>(jumble.size()) };

    for (int i{ 0 }; i < length; ++i) {
        int firstIdx{ rand() % length };
        int secondIdx{ rand() % length };
        char temp{ jumble[firstIdx] };
        jumble[firstIdx] = jumble[secondIdx];
        jumble[secondIdx] = temp;
    }

    std::cout << "\t\tWord Jumble\n\n";
    std::cout << "Unscramble the letters to make a word.\n";
    std::cout << "Enter 'hint' for a hint.\n";
    std::cout << "Enter 'quit' to quit the game.\n";
    std::cout << "The jumble is: " << jumble;

    std::string guess;
    while (guess != theWord && guess != "quit") {
        std::cout << "\n\nYour guess: ";
        std::cin >> guess;

        if (guess == "hint") {
            std::cout << theHint;
        } else if (guess == theWord) {
            std::cout << "\nThat's it! You guessed it!\n";
        } else {
            std::cout << "Sorry, that's not it";
        }
    }
}
