#ifndef CARD_HPP
#define CARD_HPP

#include <string>
using namespace std;

class Card {
  public:
    string color; // color is red/blue/yellow/green otherwiese it is 'wild'
    string types[5] = {"Skip", "Reverse", "Draw 2", "Draw 4", "Regular"};
    string chosenColor = "blank";

    
    int value; // to make it faster, special types like +4, +2, reverse, block will recieve special int values instead of separate types

    // 10 is skip
    // 11 is reverse
    // 12 is draw2

    //13 is draw4 wild
    //14 is regular wild
    Card(string color, int value) {
      this->color = color;
      this->value = value;
    }

    Card() {
      this->color = "unusable";
      this->value = -1;
    }

    // printing cards 
    void printCard() {
      if (value < 10) {
        cout << this->color << " " << this->value << endl;
      }
      else { // requires seeing the actual value since a skip isnt exactly 10
        cout << this->color << " " << types[(this->value)%10] << endl;
      }
    }
};

#endif