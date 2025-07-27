#include "game_lobby.h"
#include <iostream>

Player::Player(const std::string& name) : m_Name{ name },
                                          m_Next{ nullptr } {}

std::string Player::GetName() const {
    return m_Name;
}

Player* Player::GetNext() const {
    return m_Next;
}

void Player::SetNext(Player* next) {
    m_Next = next;
}

Lobby::Lobby() : m_Head{ nullptr } {}

Lobby::~Lobby() {
    Clear();
}

void Lobby::AddPlayer() {
    std::cout << "Please enter the name of the player: ";
    std::string name;
    std::cin >> name;
    Player* newPlayer{ new Player{ name } };

    if (m_Head == nullptr) {
        m_Head = newPlayer;
    } else {
        Player* iter = m_Head;
        while (iter->GetNext() != nullptr) {
            iter = iter->GetNext();
        }
        iter->SetNext(newPlayer);
    }
}
