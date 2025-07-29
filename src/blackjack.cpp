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

    for (int s{ Card::CLUBS }; s <= Card::SPADES; ++s) {
        for (int r{ Card::ACE }; r <= Card::KING; ++r) {
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

Game::Game(const std::vector<std::string>& names) {
    std::vector<std::string>::const_iterator name;
    for (name = names.begin(); name != names.end(); ++name) {
        m_Players.push_back(Player{ *name });
    }

    m_Deck.Populate();
    m_Deck.Shuffle();
}

Game::~Game() {}

void Game::Play() {
    std::vector<Player>::iterator player;
    for (int i{ 0 }; i < 2; ++i) {
        for (player = m_Players.begin(); player != m_Players.end(); ++player) {
            m_Deck.Deal(*player);
        }

        m_Deck.Deal(m_House);
    }

    m_House.FlipFirstCard();

    for (player = m_Players.begin(); player != m_Players.end(); ++player) {
        m_Deck.AdditionalCards(*player);
    }

    m_House.FlipFirstCard();
    std::cout << "\n"
              << m_House;

    m_Deck.AdditionalCards(m_House);

    if (m_House.IsBusted()) {
        for (player = m_Players.begin(); player != m_Players.end(); ++player) {
            if (!player->IsBusted()) {
                player->Win();
            }
        }
    } else {
        for (player = m_Players.begin(); player != m_Players.end(); ++player) {
            if (player->IsBusted()) {
                continue;
            }

            if (player->GetTotal() > m_House.GetTotal()) {
                player->Win();
            } else if (player->GetTotal() < m_House.GetTotal()) {
                player->Lose();
            } else {
                player->Push();
            }
        }
    }

    for (player = m_Players.begin(); player != m_Players.end(); ++player) {
        player->Clear();
    }

    m_House.Clear();
}

void blackjack() {
    std::cout << "\t\tBlackjack\n";

    int numPlayers{ 0 };
    while (numPlayers < 1 || numPlayers > 7) {
        std::cout << "How many players [1 - 7]: ";
        std::cin >> numPlayers;
    }

    std::vector<std::string> names;
    std::string name;
    for (int i{ 0 }; i < numPlayers; ++i) {
        std::cout << "Enter the player name:";
        std::cin >> name;
        names.push_back(name);
    }

    std::cout << "\n";

    Game game{ names };
    char again{ 'y' };
    while (again != 'n' && again != 'N') {
        game.Play();
        std::cout << "Do you want to play again? (Y/N): ";
        std::cin >> again;
    }
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    const std::string RANKS[]{ "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    const std::string SUITS[]{ "C", "D", "H", "S" };

    if (card.m_isFaceUp) {
        os << RANKS[card.m_Rank] << SUITS[card.m_Suit];
    } else {
        os << "XX";
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& genericPlayer) {
    os << genericPlayer.m_Name << ":\t";

    std::vector<Card*>::const_iterator card;
    if (genericPlayer.m_Cards.empty()) {
        os << "<empty>";
        return os;
    }

    for (card = genericPlayer.m_Cards.begin(); card != genericPlayer.m_Cards.end(); ++card) {
        os << *(*card) << "\t";
    }

    os << "(" << genericPlayer.GetTotal() << ")";

    return os;
}
