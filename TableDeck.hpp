// this will represent the deck of cards
#ifndef TABLEDECK_HPP
#define TABLEDECK_HPP
#include "Card.hpp"
#include <iostream>
#include <random>

using namespace std;

class TableDeck { // 108 cards
  public:
    // per color it is: 1 zero, 2 of each 1-9, 2 of each skip/draw2/reverse = 25
    // wild cards include 4 wild card draw 4, 4 wild card
    // total thats 25*4 + 8 = 108
    vector<Card> deck; // initial deck
    vector<Card> discardPile; // discard pile
    
    
    TableDeck() {
      int decklocation = 0;

      // colored cards
      initializeColorDeck("Red");
      initializeColorDeck("Blue");
      initializeColorDeck("Green");
      initializeColorDeck("Yellow");

      // wild cards
      initializeColorDeck("Wild");

    }

    void initializeColorDeck( string color ) {

      if (color == "Wild") {
        for (int i = 13; i < 15; i++) {

          // 4 of each type
          for (int j = 0; j < 4; j++) {
            Card item(color, i);
            deck.push_back(item);
          }
        }
      } 

      else {
        // initialize the single 0 card of that color
        Card item(color, 0);
        deck.push_back(item);

        // initialize the other 9 cards
        for (int i = 1; i < 13; i++) {
          Card one(color, i);
          deck.push_back(one);
          Card two(color, i);
          deck.push_back(two);
        } 
      }
    }

    void printDeck() {
      for (int i = 0; i < deck.size(); i++) {
        cout << deck[i].color;
        cout << deck[i].value << endl;
      }
    }

};
#endif