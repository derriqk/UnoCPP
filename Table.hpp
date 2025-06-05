#include "TableDeck.hpp"
#include "Player.hpp"
#ifndef TABLE_HPP
#define TABLE_HPP
// this will create the table deck as well as the players
class Table {
  public: 
    TableDeck game;
    Player* players; // 3 players
    int currentCard = 0;
    int playercount;
    int cardcount;

    Table(int size, int cardcount) {
      game.shuffleDeck();
      this->players = new Player[size];
      this->playercount = size;
      this->cardcount = cardcount;
    }

    // destructor
    ~Table() {
      delete[] players;   
    }

    void initializeHands() {
      for (int i = 0; i < playercount; i++) {
        for (int j = 0; j < cardcount; j++) {
          (players[i].hand).push_back(game.deck[currentCard]);
          currentCard++;
        }
      }
    }
};


#endif