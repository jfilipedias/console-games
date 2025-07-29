#include "game_lobby.h"
#include <iostream>

Player::Player(const std::string& name)
    : m_Name{ name },
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

Lobby::Lobby()
    : m_Head{ nullptr } {}

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

void Lobby::RemovePlayer() {
    if (m_Head == nullptr) {
        std::cout << "The game lobby is empty. No one to remove!\n";
    } else {
        Player* temp = m_Head;
        m_Head = m_Head->GetNext();
        delete temp;
    }
}

void Lobby::Clear() {
    while (m_Head != nullptr) {
        RemovePlayer();
    }
}

std::ostream& operator<<(std::ostream& os, const Lobby& aLobby) {
    Player* iter = aLobby.m_Head;

    os << "\nHere's who's in the game lobby:\n";
    if (iter == nullptr) {
        os << "The lobby is empty.\n";
    } else {
        while (iter != nullptr) {
            os << iter->GetName() << "\n";
            iter = iter->GetNext();
        }
    }

    return os;
}

void gameLobby() {
    Lobby lobby;
    int choice;
    do {
        std::cout << "\t\tGame Lobby\n";
        std::cout << lobby;
        std::cout << "0 - Quit\n";
        std::cout << "1 - Add a player to the lobby\n";
        std::cout << "2 - Remove a player from the lobby\n";
        std::cout << "3 - Clear the lobby\n";
        std::cout << "Enter a choice: ";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Good bye!\n\n";
        } else if (choice == 1) {
            lobby.AddPlayer();
        } else if (choice == 2) {
            lobby.RemovePlayer();
        } else if (choice == 3) {
            lobby.Clear();
        } else {
            std::cout << "Invalid option!";
        }
    } while (choice != 0);
}
