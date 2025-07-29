#include "blackjack.h"

Card::Card(rank r, suit s, bool isFaceUp)
    : m_Rank{ r },
      m_Suit{ s },
      m_isFaceUp{ isFaceUp } {}

int Card::GetValue() const {
    int value{ 0 };
    if (m_isFaceUp) {
        value = m_Rank;
        if (value > 10) {
            value = 10;
        }
    }
    return value;
}

void Card::Flip() {
    m_isFaceUp = !m_isFaceUp;
}

Hand::Hand() {
    m_Cards.reserve(7);
}

Hand::~Hand() {
    Clear();
}

void Hand::Add(Card* card) {
    m_Cards.push_back(card);
}

void Hand::Clear() {
    std::vector<Card*>::iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        delete *iter;
        *iter = nullptr;
    }
    m_Cards.clear();
}
