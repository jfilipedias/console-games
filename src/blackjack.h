#pragma once
#include <iostream>
#include <vector>

class Card {
public:
    enum rank { ACE = 1,
                TWO,
                THREE,
                FOUR,
                FIVE,
                SIX,
                SEVEN,
                EIGHT,
                NINE,
                TEN,
                JACK,
                QUEEN,
                KING };

    enum suit { CLUBS,
                DIAMONDS,
                HEARTS,
                SPADES };

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    Card(rank r = ACE, suit s = SPADES, bool isFaceUp = true);

    int GetValue() const;
    void Flip();

private:
    rank m_Rank;
    suit m_Suit;
    bool m_isFaceUp;
};

class Hand {
public:
    Hand();
    virtual ~Hand();

    void Add(Card* card);
    void Clear();
    int GetTotal() const;

protected:
    std::vector<Card*> m_Cards;
};

void blackjack();
