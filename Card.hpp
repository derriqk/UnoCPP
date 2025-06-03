#ifndef CARD_HPP
#define CARD_HPP

#include <string>
using namespace std;

class Card {
  public:
    string color; // color is red/blue/yellow/green otherwiese it is 'wild'

    
    int value; // to make it faster, special types like +4, +2, reverse, block will recieve special int values instead of separate types

    // 10 is skip
    // 11 is reverse
    // 12 is draw2

    //13 is draw4 wild
    //14 is regular wild
};

#endif