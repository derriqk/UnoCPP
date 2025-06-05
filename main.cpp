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