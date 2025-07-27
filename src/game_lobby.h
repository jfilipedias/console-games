#pragma once
#include <string>

class Player {
  public:
    Player(const std::string& name = "");
    std::string GetName() const;
    Player* GetNext() const;
    void SetNext(Player* next);

  private:
    std::string m_Name;
    Player* m_Next;
};

class Lobby {
    friend std::ostream& operator<<(std::ostream& os, const Lobby& aLobby);

  public:
    Lobby();
    ~Lobby();
    void AddPlayer();
    void RemovePlayer();
    void Clear();

  private:
    Player* m_Head;
};
