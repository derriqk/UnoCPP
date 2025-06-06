#include <chrono>
#include <iostream>
#include <thread>
#include "Table.hpp"
#include <string>
using namespace std;


int main() {

  bool playing = true;
  string option;
  int playercount;

  // welcome message
  cout << "Hello Player 1, welcome to this game of Uno" << endl;
  std::this_thread::sleep_for(1000ms);
  cout << "Here are your options:" << endl;
  cout << "Play" << endl << "Quit" << endl;
  cout << "Please type in your selected option exactly in the terminal:" << endl;

  // get the players first option
  cin >> option;

  while (playing) {

    // if user quits the game
    if (option.compare("Quit") == 0) {
      playing = false;
      cout << "You have quit the game, thank you for playing" << endl;
    }

    // else game will begin
    else if (option.compare("Play") == 0) {
      cout << "Game will begin shortly..." << endl;
      std::this_thread::sleep_for(1000ms);
      cout << "How many players would you like to play against? (minimum 2, max 4):" << endl;
      cin >> playercount;
      
      while (cin.fail()) {
        cout << "Please enter an integer:" << endl; 
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> playercount;
      }

      while (playercount < 2 || playercount > 4) {
        cout << "Player count invalid, please retype: " << endl; 
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> playercount;
        
        while (cin.fail()) {
          cout << "Please enter an integer:" << endl; 
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          cin >> playercount;
        } 
      }

      cout << flush;
      cout << "This game will now consist of " << playercount << " Players" << endl;
      std::this_thread::sleep_for(1000ms);
      cout << "Generating the table for your game..." << endl;

      int cardcount;

      // asking to initialize the player's hands with 7 cards each minimum
      std::this_thread::sleep_for(1000ms);
      cout << "How many cards would you like to start with each? (7-12):" << endl;
      cin >> cardcount;
      
      while (cin.fail()) {
        cout << "Please enter an integer:" << endl; 
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> cardcount;
      }

      while (cardcount < 7 || cardcount > 12) {
        cout << "Card count invalid, please retype: " << endl; 
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> cardcount;
        
        while (cin.fail()) {
          cout << "Please enter an integer:" << endl; 
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          cin >> cardcount;
        } 
      }
      cout << "Initializing the hands with " << cardcount << " cards..." << endl;
      std::this_thread::sleep_for(1000ms);

      Table game(playercount, cardcount);

      game.initializeHands();
      // testing if it worked (it did, yay!)
      // game.printAllHands();
      cout << "Game will now begin... " << endl;
      std::this_thread::sleep_for(500ms);

      while (playing) {
        if (game.deckEmpty()) {
          cout << "The deck is empty, taking discard pile and putting into deck pile..." << endl;
          cout << "Please wait..." << endl;
          std::this_thread::sleep_for(1000ms);
          game.fixDeck();
          cout << "Deck pile has been fixed, game will continue..." << endl;
          std::this_thread::sleep_for(1000ms);
        }

        if (game.currPlayer%game.playercount == 0) { // it is the user's turn first (every time they are first for now)
          int cardnum;
          bool validCard = true;
          cout << "It is your turn Player 1..." << endl;

          // state discard pile card
          std::this_thread::sleep_for(500ms);
          cout << endl << "The card on the discard pile is: ";
          game.viewDiscard();
          cout << endl;

          cout << "Your hand is:" << endl;
          game.players[0].printHand();

          cout << "Which card are you using? Please type the integer that correlates to the card:" << endl;
          cout << "Otherwise if no card can be used, please type 0 to draw until valid" << endl;

          cin >> cardnum;

          // this is for the user's turn
          while (validCard) {
            while (cin.fail()) {
              cout << "Please enter an integer:" << endl; 
              cin.clear();
              cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              cin >> cardnum;
            }

            while (cardnum < 0 || cardnum > game.players[0].hand.size()) {
              cout << "Please enter a valid card number:" << endl; 
              cin.clear();
              cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              cin >> cardnum;
            }

            if (cardnum == 0) { // draw until valid
              bool cont = true;
              game.drawCard(game.players[0]);

              cout << "You decide to play: ";
              game.players[0].hand.back().printCard();
              cout << endl;

              if (game.playCard(game.players[0].hand.back(), game.players[0].hand.size()-1)) {
                cout << "Next Player's turn..." << endl; 
                std::this_thread::sleep_for(500ms);
                validCard = false;
              }
            } 
            else { // play that card
              cout << "You decide to play: ";
              game.players[0].hand[cardnum - 1].printCard(); 
              cout << endl;

              if (game.playCard(game.players[0].hand[cardnum-1], cardnum-1)) {
                cout << "Next Player's turn..." << endl; 
                std::this_thread::sleep_for(500ms);
                validCard = false;
              } 
              else {
                cout << "Card could not be used, use another card!" << endl; 
                cout << "Please enter an integer:" << endl; 
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> cardnum;
              }
            }
          }
        } 
        else { // the 'bot' will play otherwise
           cout << "It is Player " << game.currPlayer%game.playercount + 1 << "'s turn..." << endl;

            // state discard pile card
            std::this_thread::sleep_for(500ms);
            cout << endl << "The card on the discard pile is: ";
            game.viewDiscard();
            cout << endl;

            cout << "Player " << game.currPlayer%game.playercount + 1<< " is deciding their move..." << endl;
            std::this_thread::sleep_for(1500ms);
            game.botPlay(game.players[game.currPlayer%game.playercount]);
        }
      }
      

      

      std::this_thread::sleep_for(12000ms);
    }

    // restate the game options
    else {
      cout << "Please type in your selected option exactly in the terminal:" << endl;
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cin >> option;
    }
  }

  return 0;
}