#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "Card.hpp"

using namespace std;

/*
Class - Player
    Purpose: To encapsulate all identification needed for an individual player in one centralized class.
    Members
        Private
            - hand (vector<Card>): variable
                A list of cards which the player holds.
            - out (bool): variable
                The tetermining variable on whether the player has lost the game.
            - nextPlayer (Player*): variable
                Utilized to determine the next player in the game. In GamePlayer, this system is setup as a linked list.
        
        Public
            - Player(): method
                All this cunstrucotr currently does is set the out variable to false
            - read_hand() (vecotor<Card>): method
                Returns the hand variable. This is const because nothing should ever be altered in this function.
            - read_nextPlayer() (Player*): method
                Retruns the nextPlayer variable. This is const because nothing should ever be altered in this function.
            - draw_card(Card) (void): method
                Adds one card, which is given through the input, to the hand variable.
            - set_nextPlayer(Player*) (void): method
                Used in the GamePlay file, in the make_player_list() method in order to set the linked list. Cannot be done at the creation of the players because a minimum of two Players must already exists in order to set one as the nextPlayer to the other.

*/
class Player {
private:
    // Variables
    vector<Card> hand;
    bool out;
    Player* nextPlayer;

public:
    // Methods
    Player();
    vector<Card> read_hand() const;
    bool read_out() const;
    Player* read_nextPlayer() const;
    void draw_card(Card);
    void set_nextPlayer(Player*);
};

#endif