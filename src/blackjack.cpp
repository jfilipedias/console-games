#include "blackjack.h"
#include <algorithm>
#include <random>

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

int Hand::GetTotal() const {
    if (m_Cards.empty()) {
        return 0;
    }

    if (m_Cards[0]->GetValue() == 0) {
        return 0;
    }

    int total{ 0 };
    std::vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        total += (*iter)->GetValue();
    }

    bool containsAce{ false };
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        if ((*iter)->GetValue() == Card::ACE) {
            containsAce = true;
        }
    }

    // Treat ace as 11 once the total is low enough.
    if (containsAce && total <= 11) {
        // Add only 10 since the previous count already added 1 for the ace.
        total += 10;
    }

    return total;
}

GenericPlayer::GenericPlayer(const std::string& name)
    : m_Name{ name } {}

GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::IsBusted() const {
    return GetTotal() > 21;
}

void GenericPlayer::Bust() const {
    std::cout << m_Name << " busts.\n";
}

Player::Player(const std::string& name)
    : GenericPlayer{ name } {}

Player::~Player() {}

bool Player::IsHitting() const {
    std::cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    std::cin >> response;
    return response == 'y' || response == 'Y';
}

void Player::Win() const {
    std::cout << m_Name << " wins.\n";
}

void Player::Lose() const {
    std::cout << m_Name << " loses.\n";
}

void Player::Push() const {
    std::cout << m_Name << " pushes.\n";
}

House::House(const std::string& name)
    : GenericPlayer{ name } {}

House::~House() {}

bool House::IsHitting() const {
    return GetTotal() <= 16;
}

void House::FlipFirstCard() {
    if (!m_Cards.empty()) {
        m_Cards[0]->Flip();
    } else {
        std::cout << "No card to flip!\n";
    }
}

Deck::Deck() {
    m_Cards.reserve(52);
    Populate();
}

Deck::~Deck() {}

void Deck::Populate() {
    Clear();

    for (int s = Card::CLUBS; s <= Card::SPADES; ++s) {
        for (int r = Card::ACE; r <= Card::KING; ++r) {
            Add(new Card{ static_cast<Card::rank>(r), static_cast<Card::suit>(s) });
        }
    }
}

void Deck::Shuffle() {
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::shuffle(m_Cards.begin(), m_Cards.end(), gen);
}

void Deck::Deal(Hand& hand) {
    if (!m_Cards.empty()) {
        hand.Add(m_Cards.back());
        m_Cards.pop_back();
    } else {
        std::cout << "Out of cards. Unable to deal.";
    }
}

void Deck::AdditionalCards(GenericPlayer& genericPlayer) {
    std::cout << "\n";
    while (!genericPlayer.IsBusted() && genericPlayer.IsHitting()) {
        Deal(genericPlayer);
        std::cout << genericPlayer << "\n";

        if (genericPlayer.IsBusted()) {
            genericPlayer.Bust();
        }
    }
}
