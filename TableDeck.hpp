// this will represent the deck of cards
#ifndef TABLEDECK_HPP
#define TABLEDECK_HPP
#include "Card.hpp"
#include <iostream>
#include <random>

using namespace std;

class TableDeck { // 108 cards
  public:
    Card deck[108];
    // per color it is: 1 zero, 2 of each 1-9, 2 of each skip/draw2/reverse = 25
    // wild cards include 4 wild card draw 4, 4 wild card
    // total thats 25*4 + 8 = 108
    
    TableDeck() {
      int decklocation = 0;

      // colored cards
      initializeColorDeck("red", decklocation);
      initializeColorDeck("blue", decklocation);
      initializeColorDeck("green", decklocation);
      initializeColorDeck("yellow", decklocation);

      // wild cards
      initializeColorDeck("wild", decklocation);

    }

    void initializeCard(Card& card, string color, int value) {
      card.color = color;
      card.value = value;
    }

    void initializeColorDeck( string color, int& location) {

      if (color == "wild") {
        for (int i = 13; i < 15; i++) {

          // 4 of each type
          for (int j = 0; j < 4; j++) {
            initializeCard(deck[location], color, i);
            location++;
          }

        }
      } 

      else {
        // initialize the single 0 card of that color
      initializeCard(deck[location], color, 0);
      location++;

      // initialize the other 9 cards
      for (int i = 1; i < 13; i++) {
        initializeCard(deck[location], color, i);
        location++;
        initializeCard(deck[location], color, i);
        location++;
      } 
      }

      
    }

    void printDeck() {
      for (int i = 0; i < 108; i++) {
        cout << deck[i].color;
        cout << deck[i].value << endl;
      }
    }

    void shuffleDeck() {

      std::random_device rd;
      std::mt19937 gen(rd());

      for (int i = 0; i < 108; i ++) {
        std::uniform_int_distribution<> distrib(i, 107);
        int randomIndex = distrib(gen);

        Card temp = deck[i];
        deck[i] = deck[randomIndex];
        deck[randomIndex] = temp;
      }
    }
};
#endif