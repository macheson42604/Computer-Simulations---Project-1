#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "Card.hpp"

using namespace std;

// TODO: update this comment
/*
Class - Player
    Purpose: To encapsulate all identification needed for an individual player in one centralized class.
    Members
        Private
            - playingHand (vector<Card>): variable
                A list of cards which the player holds and plays from during the game.
            - winningHand (vector<Card>): variable
                A list of cards which the player has won during the game, but has not yet shuffled into their playing hand.
            - numWins (int): variable
                The number of games the player has won.
            - isOut (bool): variable
                The determining variable on whether the player has lost the game.

        Public
            - Player(): method
                Initialized playingHand and winningHand to empty vectors, isOut to false (because players are just starting to play the game), and numWins to 0.
            - draw_from_playing_hand() (Card): method
                Draws the top card from the playing hand and removes it from the playing hand.
            - add_to_winning_hand(const vector<Card>) (void): method
                Appends all the cards being added to the current winning hand vector.
            - move_winning_to_playing() (void): method
                Moves all cards from the winning hand to the playing hand. First checks that the playing hand is empty, and shuffles the winning hand before moving it to the playing hand.
            - increment_wins() (void): method
                Increments the numWins variable by 1.
            - set_isOut(const bool) (void): method
                Sets the isOut variable to true.
            - read_playing_hand() (vector<Card>): method
                Returns the playingHand variable. This is const because nothing should ever be altered in this function.
            - read_winning_hand() (vector<Card>): method
                Returns the winningHand variable. This is const because nothing should ever be altered in this function.
            - read_isOut() (bool): method
                Returns the isOut variable. This is const because nothing should ever be altered in this function.
            - read_numWins() (int): method
                Returns the numWins variable. This is const because nothing should ever be altered in this function
*/

class Player {
    private:
        // Variables
        vector<Card> playingHand;
        vector<Card> winningHand;
        bool isOut;
        int numWins;

    public:
        // Methods
        Player();
        
        // Methods for War
        Card draw_from_playing_hand();
        void add_to_winning_hand(const vector<Card>);
        void move_winning_to_playing();

        // Mutator (setter) methods
        void increment_wins();
        void set_isOut(const bool);

        // Accessor (getter) methods
        vector<Card> read_playing_hand() const;
        vector<Card> read_winning_hand() const;
        bool read_isOut() const;
        int read_numWins() const;
        int read_num_cards() const;

};

#endif