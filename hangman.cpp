#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void hangman() {
    const int MAX_WRONG_GUESSES{ 8 };

    std::vector<std::string> words;
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");

    std::random_device rd;
    std::mt19937 mt(rd());
    std::shuffle(words.begin(), words.end(), mt);

    const std::string THE_WORD{ words[0] };
    int wrongGuesses{ 0 };
    std::string lettersGuessed(THE_WORD.size(), '_');
    std::string triedLetters{ "" };

    std::cout << "\t\tHangman\n";

    while (wrongGuesses < MAX_WRONG_GUESSES && lettersGuessed != THE_WORD) {
        std::cout << "\nYou have " << wrongGuesses << " incorrect guesses";
        std::cout << "\nYou've used the following letters: " << triedLetters;
        std::cout << "\nSo far, the word is: " << lettersGuessed;
    }
}
