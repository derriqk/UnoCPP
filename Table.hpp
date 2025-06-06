#include "TableDeck.hpp"
#include "Player.hpp"
#ifndef TABLE_HPP
#define TABLE_HPP
// this will create the table deck as well as the players
class Table {
  public: 
    TableDeck game;
    int currPlayer; // atm first player will always be player 1
    bool direction = true; // true means right, false means left

    Player* players; // 3 players
    int playercount;
    int cardcount;
    string chosenColor; // this changes as the game goes on

    Table(int size, int cardcount) {
      shuffleDeck();
      this->players = new Player[size];
      
      this->playercount = size;
      this->cardcount = cardcount;

      players[0].role = "user"; // assign user to first player
      currPlayer = 100*size;
      // players[2].role = "user";

      // debugging
      // game.printDeck(); 
      // cout << "direction is: " << direction << endl;
      // Card test("Red", 5);
      // // Card test2("Red", 1);
      // // Card test3("Wild", 13);
      // game.deck.push_back(test);
      // // players[0].hand.push_back(test2); // add a test card to the first player
      // // players[1].hand.push_back(test3); // add a test card to the next player
      // game.deck.clear();
      // Card test4("Wild", 14);

      // game.deck.push_back(test4);
      // game.deck.push_back(test4);
      // game.deck.push_back(test4);
      // game.deck.push_back(test4);


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
        cout << "The previous player changed the color to " << chosenColor << endl;
      } 
      else if (game.discardPile.back().value == 14) {
        cout << game.discardPile.back().color << " Regular" << endl;
        cout << "The previous player changed the color to " << chosenColor << endl;
      }
      else {
        (game.discardPile.back()).printCard();
      }
    }

    void drawCard(Player& player) {
      if (deckEmpty()) {
        cout << "The deck is empty, taking discard pile and putting into deck pile..." << endl;
        cout << "Please wait..." << endl;
        std::this_thread::sleep_for(1000ms);
        fixDeck();
        cout << "Deck pile has been fixed, game will continue..." << endl;
        std::this_thread::sleep_for(1000ms);
      }

      player.hand.push_back(game.deck.back());
      game.deck.pop_back();

      // only reveal drawn cards to players
      if (player.role == "user") { // print the card they drew
        cout << "Card drawn: ";
        player.hand.back().printCard();
        cout << endl;
        std::this_thread::sleep_for(700ms);
      } else {
        cout << "Player " << (currPlayer%playercount) + 1 << " has drawn a card" << endl;
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
        compare = chosenColor;
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
        compare = chosenColor;
      } else {
        compare = game.discardPile.back().color;
      }

      if (card.value == game.discardPile.back().value || card.color == compare || card.value > 12) { // wild cards can always be used
        result = true;

        int playedValue = card.value; // save the value of the played card;

        // now add to discard pile the card the user used, and remove from user

        // before: (debug)
        // players[0].printHand();
        // game.discardPile.back().printCard();

        // add removed card to discard pile
        game.discardPile.push_back(card);
        // overrride the chosen card then remove it
        if (deckEmpty()) {
          cout << "Deck is empty, moving discard to the deck and reshuffling..." << endl;
          fixDeck();
        }
        players[currPlayer%playercount].hand[location] = players[currPlayer%playercount].hand.back();
        players[currPlayer%playercount].hand.pop_back();

        // checks for special cards
        if (playedValue == 10) { // skip card
          cout << "Player " << (currPlayer%playercount) + 1 << " has skipped the next player" << endl;
          if (direction) { // direction is right so increment instead
            currPlayer ++; 
          } else { // directon is left so decrement instead
            currPlayer --; 
          }
          std::this_thread::sleep_for(500ms);
        }
        else if (playedValue == 11) { // reverse card
          cout << "Player " << (currPlayer%playercount) + 1 << " has reversed the turn order" << endl;
          std::this_thread::sleep_for(500ms);
          direction = !direction; // reverse the direction
        }
        else if (playedValue == 12) { // draw 2 and skip (no stacking made just yet)
          if (direction) {
            cout << "Player " << ((currPlayer+1)%playercount) + 1 << " has to draw 2 and skip their turn" << endl;
          } else {
            cout << "Player " << ((currPlayer-1)%playercount) + 1 << " has to draw 2 and skip their turn" << endl;
          }
          std::this_thread::sleep_for(1000ms);
          // skip after drawing
          if (direction) { // direction is right so increment instead
            drawNum(2, players[(currPlayer+1)%playercount]); // next player draws 2 cards
            currPlayer ++; 
          } else { // directon is left so decrement instead
            drawNum(2, players[(currPlayer-1)%playercount]); // next player draws 2 cards
            currPlayer --; 
          }
        }
        else if (playedValue == 13) { // draw 4 wild (no stacking made just yet)
          cout << "Player " << (currPlayer%playercount) + 1 << " has used a Wild Draw 4 Card" << endl;
          std::this_thread::sleep_for(1000ms);
          
          if (players[currPlayer%playercount].role == "user") { // let them choose
            cout << "Which color would you like to use? Please type the number option:" << endl;
            cout << "1: Red" << endl << "2: Blue" << endl << "3: Green" << endl << "4: Yellow" << endl;

            bool validInput = true;
            int inputNum;
            string colors[4] = {"Red", "Blue", "Green", "Yellow"};

            cin >> inputNum;
            while (validInput) {
              while (cin.fail()) {
                cout << "Please enter an integer:" << endl; 
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> inputNum;
              }

              while (inputNum < 1 || inputNum > 4) {
                cout << "Please enter a valid card number:" << endl; 
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> inputNum;
              }

              if (!cin.fail() && (inputNum > 1 || inputNum < 4)) {
                validInput = false;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              }
            }

            chosenColor = colors[inputNum-1]; // set the chosenColor
            cout << "Chosen color is now: " << chosenColor << endl;
          }
          else { // not a player, make random color chooser
            cout << "Player " << (currPlayer%playercount) + 1 << " is choosing their color..." << endl;
            std::random_device rd;
            std::mt19937 gen(rd());

            string colors[4] = {"Red", "Blue", "Green", "Yellow"};

            std::uniform_int_distribution<> distrib(0, 3);
            int randomIndex = distrib(gen);
            chosenColor = colors[randomIndex]; // set the chosenColor
            cout << "Chosen color is now: " << chosenColor << endl;
          }

          std::this_thread::sleep_for(1000ms);
          
          if (direction) {
            cout << "Player " << ((currPlayer+1)%playercount) + 1 << " has to draw 4 and skip their turn" << endl;
          } else {
            cout << "Player " << ((currPlayer-1)%playercount) + 1 << " has to draw 4 and skip their turn" << endl;
          }

          if (direction) { // direction is right so increment instead
            drawNum(4, players[(currPlayer+1)%playercount]); // next player draws 4 cards
            currPlayer ++; 
          } else { // directon is left so decrement instead
            drawNum(4, players[(currPlayer-1)%playercount]); // next player draws 4 cards
            currPlayer --; 
          }
        }
        else if (playedValue == 14) { // regular wild
          cout << "Player " << (currPlayer%playercount) + 1 << " has used a Wild Card" << endl;
          std::this_thread::sleep_for(1000ms);
          
          if (players[currPlayer%playercount].role == "user") { // let them choose
            cout << "Which color would you like to use? Please type the number option:" << endl;
            cout << "1: Red" << endl << "2: Blue" << endl << "3: Green" << endl << "4: Yellow" << endl;

            bool validInput = true;
            int inputNum;
            string colors[4] = {"Red", "Blue", "Green", "Yellow"};

            cin >> inputNum;
            while (validInput) {
              while (cin.fail()) {
                cout << "Please enter an integer:" << endl; 
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> inputNum;
              }

              while (inputNum < 1 || inputNum > 4) {
                cout << "Please enter a valid card number:" << endl; 
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> inputNum;
              }

              if (!cin.fail() && (inputNum > 1 || inputNum < 4)) {
                validInput = false;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              }
            }

            chosenColor = colors[inputNum-1]; // set the chosenColor
            cout << "Chosen color is now: " << chosenColor << endl;
          }
          else { // not a player, make random color chooser
            cout << "Player " << (currPlayer%playercount) + 1 << " is choosing their color..." << endl;
            std::random_device rd;
            std::mt19937 gen(rd());

            string colors[4] = {"Red", "Blue", "Green", "Yellow"};

            std::uniform_int_distribution<> distrib(0, 3);
            int randomIndex = distrib(gen);
            chosenColor = colors[randomIndex]; // set the chosenColor
            cout << "Chosen color is now: " << chosenColor << endl;
          }
          std::this_thread::sleep_for(1000ms);
        }

        // since player turn succeeded, increment/decrement currPlayer
        if (direction) { // direction is right so increment instead
          currPlayer ++; 
        } else { // directon is left so decrement instead
          currPlayer --; 
        }

        // prevent negatives
        if (currPlayer < 50) {
          currPlayer += playercount * 5;
        }

        // after: (debug)
        // players[0].printHand();
        // game.discardPile.back().printCard();
      }
      return result;
    }

    void drawNum(int num, Player& player) {
      if (direction) {
        cout << "Player " << (currPlayer+1)%playercount + 1 << " is drawing " << num << " cards..." << endl;
      } else {
        cout << "Player " << (currPlayer-1)%playercount + 1 << " is drawing " << num << " cards..." << endl;
      }
      std::this_thread::sleep_for(500ms);
      // testing purposes:
      // player.printHand();

      for (int i = 0; i < num; i++) {

        if (deckEmpty()) {
          cout << "The deck is empty, taking discard pile and putting into deck pile..." << endl;
          cout << "Please wait..." << endl;
          std::this_thread::sleep_for(1000ms);
          fixDeck();
          cout << "Deck pile has been fixed, game will continue..." << endl;
          std::this_thread::sleep_for(1000ms);
        }
        
        player.hand.push_back(game.deck.back());
        game.deck.pop_back();

        if (player.role == "user") { // print the card they drew
          cout << "Card drawn: ";
          player.hand.back().printCard();
          cout << endl;
          std::this_thread::sleep_for(1000ms);
        } else { // bot drawing so dont show the card
          if (direction) {
            cout << "Player " << (currPlayer+1)%playercount + 1 << " has drawn a card" << endl;
          } else {
            cout << "Player " << (currPlayer-1)%playercount + 1 << " has drawn a card" << endl;
          }
          std::this_thread::sleep_for(1000ms);
        }
      }
      // testing purposes:
      // player.printHand(); // print the hand after drawing
    }

    // check if a bot has a valid hand to use
    void botPlay(Player& player, bool& uno) {
      int i = 0;
      // cout << "TESTING 1" << endl;

      // check every card in the bot's hand
      while (i < player.hand.size() && !canUse(player.hand[i])) {
        i++;
      }

      // cout << "TESTING 2" << endl;
      if (!canUse(player.hand[i])) {
        cout << "Player " << (currPlayer%playercount) + 1 << " is now drawing cards... " << endl;
        // cout << "TESTING 3" << endl;
        drawCard(player);
        
        cout << "Player " << (currPlayer%playercount) + 1 << " decides to play: " << endl;
        player.hand.back().printCard();
        cout << endl;
        // cout << "TESTING 4" << endl;

        if (winner(player)) {
          // cout << "TESTING 5" << endl;
          cout << "Player " << (currPlayer%playercount) + 1 << "wins the game! " << endl;
          uno = false;
        }
        

        if (playCard(player.hand.back(), player.hand.size()-1)) {
        // cout << "TESTING 6" << endl;
        cout << "Next Player's turn..." << endl; 
        std::this_thread::sleep_for(500ms);
        }
      }
      else {
        // cout << "TESTING 7" << endl;
        cout << "Player " << (currPlayer%playercount) + 1 << " decides to play: " << endl;
        player.hand[i].printCard();
        cout << endl;

        if (winner(player)) {
          // cout << "TESTING 8" << endl;
          cout << "Player " << (currPlayer%playercount) + 1 << "wins the game! " << endl;
          uno = false;
        }

        // cout << "TESTING 9" << endl;
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

    bool winner(Player& player) {
      return player.hand.empty();
    }
};


#endif