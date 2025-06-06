#include <string>
#include <iostream>

using namespace std;

int main() {


  int currPlayer = 1000;
  int playercount = 4; // Example player count
  currPlayer+=2;
  currPlayer += 100 * playercount; // Ensure positivity

  string players[] = {"Player 1", "Player 2", "Player 3", "Player 4"};
  cout << "It is Player " << (currPlayer % playercount) + 1 << "'s turn..." << endl;



  return 0;
}