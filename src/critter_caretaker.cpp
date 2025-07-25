#include "critter_caretaker.h"
#include <iostream>

Critter::Critter(int hunger, int boredom) : m_hunger{ hunger },
                                            m_boredom{ boredom } {}

inline int Critter::GetMood() const {
    return m_hunger + m_boredom;
}

void Critter::PassTime(int time) {
    m_hunger += time;
    m_boredom += 1;
}

void Critter::Talk() {
    int mood{ GetMood() };

    std::cout << "\nI'm a critter and I fell ";
    if (mood > 15) {
        std::cout << "mad.\n";
    } else if (mood > 10) {
        std::cout << "frustrated.\n";
    } else if (mood > 5) {
        std::cout << "okay.\n";
    } else {
        std::cout << "happy.\n";
    }

    PassTime();
}

void Critter::Eat(int food) {
    std::cout << "\nBrruppp.\n";

    m_hunger -= food;
    if (m_hunger < 0) {
        m_hunger = 0;
    }

    PassTime();
}

void Critter::Play(int fun) {
    std::cout << "\nWheee!\n";

    m_boredom -= fun;
    if (m_boredom < 0) {
        m_boredom = 0;
    }

    PassTime();
}

void critterCaretaker() {
    std::cout << "\t\tCritter Caretaker.\n";
    Critter crit;
    crit.Talk();

    int choice;
    do {
        std::cout << "\n0 - Quit";
        std::cout << "\n1 - Listen to your critter";
        std::cout << "\n2 - Feed your critter";
        std::cout << "\n3 - Play with your critter";

        std::cout << "\nChoice: ";
        std::cin >> choice;
        switch (choice) {
        case 0:
            std::cout << "\nGoodbye.\n";
            break;
        case 1:
            crit.Talk();
            break;
        case 2:
            crit.Eat();
            break;
        case 3:
            crit.Play();
            break;
        default:
            std::cout << "\nSorry, but " << choice << " isn't a valid choice.\n";
        }
    } while (choice != 0);
}
