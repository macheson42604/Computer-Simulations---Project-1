#include "Player.hpp"
#include "GamePlay.hpp"
#include <vector>
using namespace std;

// Constructor
// initialize playing and winning hands to empty vectors
// set isOut to false (because they're just starting to play the game)
// initialize numWins to 0
Player::Player() {
    playingHand = vector<Card>();
    winningHand = vector<Card>();
    isOut = false;
    numWins = 0;
}

// Destructor
Player::~Player() {
    delete playingHand;
    delete winningHand;
}

// Methods for War
Card draw_from_playing_hand() {
    // draw top card from the playing hand
    if (playingHand.empty()) {
        cerr << "Error: cannot draw from playing hand because it is empty" << endl;
        return Card(); 
    }

    // top of the deck will be considered the last card in the vector (thus pop_back is acceptable)
    Card topCard = playingHand.back();
    // remove top card from playing hand because we we'll be playing this card
    playHand.pop_back();
    return topCard;
}

void add_to_winning_hand(const vector<Card> & addCards) {
    if (addCards.empty()) {
        cerr << "Error: cannot add to winning hand because the input vector is empty" << endl;
        return;
    }

    // append all the cards being added to the current winning hand vector
    winningHand.insert(winningHand.end(), addCards.begin(), addCard.end());
}

void move_winning_to_play() {
    // first check playing hand is empty (give error else)
    if (!playingHand.empty()) {
        cerr << "Error: cannot move winning hand to playing hand because playing hand is not empty" << endl;
        return;
    }

    // check if addCards is empty (player should be out if they have no playing hand and no winning hand)
    if (winningHand.empty()) {
        cerr << "Error: cannot move winning hand to playing hand because winning hand is empty" << endl;
        return;
    }

    // shuffle winning hand using the shuffle function from GamePlay
    shuffle_cards(this->winningHand);

    // append winning hand vector to the playing hand vector
    playingHand.insert(playingHand.end(), winningHand.begin(), winningHand.end());

    // erase all of the cards from the winning hand
    winningHand.clear();

    if (!winningHand.empty()) {
        cerr << "Error: winning hand should be empty after moving to playing hand, but it is not" << endl;
    }
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
    if (numWins < 0) {
        cerr << "Error: numWins should never be negative, but it is " << numWins << endl;
    }
    
    return numWins;
}

int read_num_cards() const {
    return playingHand.size() + winningHand.size();
}