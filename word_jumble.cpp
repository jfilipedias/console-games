#include "word_jumble.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void wordJumble() {
    srand(static_cast<unsigned int>(time(0)));
    int randNumber{ rand() % 100 + 1 };

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

    srand(static_cast<unsigned int>(time(0)));
    int choice = (rand() % NUM_WORDS);
    std::string theWord = WORDS[choice][WORD];
    std::string theHint = WORDS[choice][HINT];

    std::cout << "Wellcome to Word Jumble!!!\n\n";
    std::cout << "Enter 'hint' for a hint.\n";
    std::cout << "Enter 'quit' to quit the game.\n";
}
