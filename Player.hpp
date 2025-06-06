#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
  public:
    vector<Card> hand;// player will hold cards in this list
    string role = "bot";

    void printHand() {
      for (int i = 0; i < hand.size(); i ++) {
        int num = i + 1;
        cout << "Card #" << num << ": ";
        hand[i].printCard();
      }
    }
};

#endif