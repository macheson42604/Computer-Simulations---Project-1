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
    Player* currentPlayer = make_player_list();
}

// Creates a linked list between the two players
Player* make_player_list() {
    // Make Both Players
    Player* firstPlayer = new Player();
    Player* secondPlayer = new Player();

    // Set nextPlayer to each other
    firstPlayer->set_nextPlayer(secondPlayer);
    secondPlayer->set_nextPlayer(firstPlayer);

    return firstPlayer;
}