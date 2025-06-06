#include "TableDeck.hpp"
#include "Player.hpp"
#ifndef TABLE_HPP
#define TABLE_HPP
// this will create the table deck as well as the players
class Table {
  public: 
    TableDeck game;
    int currPlayer = 0; // atm first player will always be player 1
    string direction = "right";

    Player* players; // 3 players
    int playercount;
    int cardcount;

    Table(int size, int cardcount) {
      shuffleDeck();
      this->players = new Player[size];
      players[0].role = "user"; // assign user to first player
      this->playercount = size;
      this->cardcount = cardcount;

      // game.printDeck(); debugging
      Card test("Red", 5);
      Card test2("Red", 11);
      game.deck.push_back(test);
      players[0].hand.push_back(test2); // add a test card to the first player

      // add the first card to the discard pile, then remove from deck
      if ( game.deck.back().value > 10) { // cant really add a wild/special card to the discard pile first
        int i = 0;
        
        while ((game.deck[i].value > 10) && i < game.deck.size()) {
          i++;
        }

        // once valid card is found, swap them
        Card temp = game.deck[i];
        game.deck[i] = game.deck[game.deck.size()-1];
        game.deck[game.deck.size()-1] = temp;
      }

      addToDiscard(game.deck.back());
      game.deck.pop_back();
    }

    // destructor
    ~Table() {
      delete[] players;   
    }

    void initializeHands() {
      for (int i = 0; i < playercount; i++) {
        for (int j = 0; j < cardcount; j++) {
          (players[i].hand).push_back(game.deck.back());
          game.deck.pop_back();
        }
      }
    }

    void printAllHands() {
      for (int i = 0; i < playercount; i++) {
        cout << "Player " << i + 1 << " has:" << endl;
        players[i].printHand();
        cout << endl;
      }
    }

    void shuffleDeck() {
      std::random_device rd;
      std::mt19937 gen(rd());

      for (int i = 0; i < game.deck.size(); i ++) {
        std::uniform_int_distribution<> distrib(i, 107);
        int randomIndex = distrib(gen);

        Card temp = game.deck[i];
        game.deck[i] = game.deck[randomIndex];
        game.deck[randomIndex] = temp;
      }
    }

    void addToDiscard(Card card) {
      game.discardPile.push_back(card);
    }

    void viewDiscard() {
      if (game.discardPile.back().value == 13) { // print the chosen color
        cout << game.discardPile.back().color << " Draw 4" << endl;
        cout << "The chosen color is now: " << game.discardPile.back().chosenColor << endl;
      } 
      else if (game.discardPile.back().value == 14) {
        cout << game.discardPile.back().color << " Regular" << endl;
        cout << "The chosen color is now: " << game.discardPile.back().chosenColor << endl;
      }
      else {
        (game.discardPile.back()).printCard();
      }
    }

    void drawCard(Player& player) {
      player.hand.push_back(game.deck.back());
      game.deck.pop_back();

      // only reveal drawn cards to players
      if (player.role == "user") { // print the card they drew
        cout << "Card drawn: ";
        player.hand.back().printCard();
        cout << endl;
        std::this_thread::sleep_for(700ms);
      } else {
        cout << "Player " << currPlayer + 1 << " has drawn a card" << endl;
      }

      if (!canUse(player.hand.back())) {
        drawCard(player);
      }
      else {
        if (player.role == "user") {
          cout << "Drawing stopped" << endl;
        }
      }
    }

    bool canUse(Card card) {
      bool result = false;
      string compare;
      if (game.discardPile.back().value > 12) {
        compare = game.discardPile.back().chosenColor;
      } else {
        compare = game.discardPile.back().color;
      }

      if (card.value == game.discardPile.back().value || card.color == compare || card.value > 12) { // wild cards can always be used
        result = true;
      }

      return result;
    }

    bool playCard(Card& card, int location) {
      bool result = false;
      string compare;

      if (game.discardPile.back().value > 12) {
        compare = game.discardPile.back().chosenColor;
      } else {
        compare = game.discardPile.back().color;
      }

      if (card.value == game.discardPile.back().value || card.color == compare) {
        result = true;

        int playedValue = card.value; // save the value of the played card;

        // now add to discard pile the card the user used, and remove from user

        // before: (debug)
        // players[0].printHand();
        // game.discardPile.back().printCard();

        // add removed card to discard pile
        game.discardPile.push_back(card);
        // overrride the chosen card then remove it
        players[currPlayer].hand[location] = players[currPlayer].hand.back();
        players[currPlayer].hand.pop_back();

        // since player turn succeeded, increment/decrement currPlayer
        
       currPlayer++;

        currPlayer = ( (currPlayer % playercount) + playercount ) % playercount;

        // after: (debug)
        // players[0].printHand();
        // game.discardPile.back().printCard();
      }
      return result;
    }

    // check if a bot has a valid hand to use
    void botPlay(Player& player) {
      int i = 0;

      // check every card in the bot's hand
      while (i < player.hand.size() && !canUse(player.hand[i])) {
        i++;
      }
      if (!canUse(player.hand[i])) {
        cout << "Bot is now drawing cards...";
        drawCard(player);
        
        cout << "Bot decides to play: ";
        player.hand.back().printCard();
        cout << endl;

        if (playCard(player.hand.back(), player.hand.size()-1)) {
        cout << "Next Player's turn..." << endl; 
        std::this_thread::sleep_for(500ms);
        }
      }
      else {
        cout << "Bot decides to play: ";
        player.hand[i].printCard();
        cout << endl;

        playCard(player.hand[i], i);
        cout << "Next Player's turn..." << endl; 
        std::this_thread::sleep_for(500ms);
      }
    }

    // these two functions are used to check if the deck is empty and to fix it
    bool deckEmpty() {
      return game.deck.size() == 0;
    }

    void fixDeck() {
      // save the current discard pile card
      Card temp = game.discardPile.back(); 
      game.discardPile.pop_back();
      game.deck = game.discardPile; 

      game.discardPile.clear();
      game.discardPile.push_back(temp); // add the saved card back to discard pile

      shuffleDeck(); // shuffle the deck again
    }
};


#endif