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
    vector<Card> playingHand;
    vector<Card> winningHand;
    bool isOut;
    int numWins;

    // the following might be extraneous
    // Player* nextPlayer;

public:
    // Methods
    Player();
    
    // Methods for War
    Card draw_from_playing_hand() const;
    void add_to_winning_hand(const vector<Card>&);
    void move_winning_to_playing();
    void shuffle_winning_hand();

    // Mutator (setter) methods
    void increment_wins();
    void clear_winning_hand();
    void set_isOut(bool);

    // Accessor (getter) methods
    vector<Card> read_playing_hand() const;
    vector<Card> read_winning_hand() const;
    bool read_isOut() const;
    int read_numWins() const;


    // the following might be extraneous
    // Player* read_nextPlayer() const;
    // void set_nextPlayer(Player*);
};

#endif