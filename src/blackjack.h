#pragma once
#include <iostream>
#include <string>
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

class GenericPlayer : public Hand {
    friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& genericPlayer);

public:
    GenericPlayer(const std::string& name = "");
    virtual ~GenericPlayer();

    virtual bool IsHitting() const = 0;
    bool IsBusted() const;
    void Bust() const;

protected:
    std::string m_Name;
};

class Player : public GenericPlayer {
public:
    Player(const std::string& name = "");
    virtual ~Player();

    virtual bool IsHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
};

class House : public GenericPlayer {
public:
    House(const std::string& name = "House");
    virtual ~House();

    virtual bool IsHitting() const;
    void FlipFirstCard();
};

class Deck : public Hand {
public:
    Deck();
    virtual ~Deck();

    void Populate();
    void Shuffle();
    void Deal(Hand& hand);
    void AdditionalCards(GenericPlayer& genericPlayer);
};

class Game {
public:
    Game(const std::vector<std::string>& names);
    ~Game();

    void Play();

private:
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;
};

void blackjack();
