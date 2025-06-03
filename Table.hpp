#include "TableDeck.hpp"
#include "Player.hpp"
#ifndef TABLE_HPP
#define TABLE_HPP
// this will create the table deck as well as the players
class Table {
  public: 
    TableDeck game;
    Player players[3]; // 3 players
    int currentCard = 0;

    Table() {
      game.shuffleDeck();
    }
};


#endif