#include <iostream>
#include <cctype>
#include <string>

#include "Card.hpp"
#include "Player.hpp"

using namespace std;

// Method Declarations
void game_setup();
Player* make_player_list();

int main() {
    game_setup();

    return 0;
}

// Method Definitions
void game_setup() {
    Player currentPlayer = make_player_list();
}

Player* make_player_list() {
    Player* humanPlayer = new Player(false); // starting player
    Player* currentPlayer = humanPlayer;

    string inputPlayers; // read in as string as this is most flexible input type
    cout << "How many opponents would you like (1-9)? ";
    cin >> inputPlayers;

    // Input sanitization
    int numPlayers = -1;
    while (numPlayers <= 0) {
        bool invalid = false;
        if (inputPlayers.size() == 1) { // Valid: 1 character long
            if (isdigit(inputPlayers[0])) { // Valid: is a digit
                if (stoi(inputPlayers) <= 0 || stoi(inputPlayers) > 9) { // Invalid: not appropriate number of players for Uno
                    invalid = true;
                } else {                                                 // Valid: appropriate number of players for Uno
                    numPlayers = stoi(inputPlayers); // this step must occur to exit the while loop
                }

            } else {                        // Invalid: not a digit
                invalid = true;
            }

        } else {                        // Invalid: more than 1 character long or 0 characters input
            invalid = true;
        }

        // Invalid input was given, repeat
        if (invalid) {
            cout << "Invalid Input, please try again..." << endl;
            cout << "How many opponents would you like (1-9)? ";
            cin >> inputPlayers;
        }

    }    

    // Create all players and link them all together
    for (int i = numPlayers; i > 0; i --) {
        Player* nextPlayer = new Player(true); /* PLACEHOLDER: All other players are initially set to computers, this could be amended */
        currentPlayer->set_nextPlayer(nextPlayer);

        currentPlayer = nextPlayer;
    }

    currentPlayer->set_nextPlayer(humanPlayer); // set last player's nextPlayer to the first player

    return humanPlayer;
}