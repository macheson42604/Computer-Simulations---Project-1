#include "Player.hpp"

using namespace std;

// Constructor
// initialize playing and winning hands to empty vectors
// set isOut to false (because they're just starting to play the game)
// initialize numWins to 0



// Methods for War
Card draw_from_playing_hand() {
    // draw top card from the playing hand
    // top of the deck will be considered the last card in the vector (thus pop_back is acceptable)
    Card topCard = playingHand.back();
    // remove top card from playing hand because we we'll be playing this card
    playHand.pop_back();
    return topCard;
}

void add_to_winning_hand(const vector<Card> & addCards) {
    // append all the cards being added to the current winning hand vector
    winningHand.insert(winningHand.end(), addCards.begin(), addCard.end());
}

void move_winning_to_play() {
    // first check playing hand is empty (give error else)

    // shuffle winning hand helper function 

    // append winning hand vector to the playing hand vector


    // erase all of the cards from the winning hand
}

void shuffle_winning_hand() {
    // same function as the one in gameplay but specifically for the winning hand as this happens throughout the round
}


// Mutator (setter) methods
void increment_wins() {
    numWins++;
}

void set_isOut(const bool) {
    isOut = true;
}



// Accessor (getter) methods
vector<Card> read_playing_hand() const {
    return playingHand;
}

vector<Card> read_winning_head() const {
    return winningHand;
}

bool read_isOut() const {
    return isOut;
}

int Player::read_numWins() const {
    return numWins;
}


// OLD FUNCTIONS
/*
Player::Player() {
    out = false;
}

vector<Card> Player::read_hand() const {
    return hand;
}

bool Player::read_out() const {
    return out;
}

Player* Player::read_nextPlayer() const {
    return nextPlayer;
}

void Player::draw_card(Card newCard) {
    hand.push_back(newCard);
}

void Player::set_nextPlayer(Player* nPlayer) {
    nextPlayer = nPlayer;
}
*/