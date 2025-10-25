#include <vector>
#include <iostream>

#include "Player.hpp"
#include "GamePlay.hpp"
#include "Card.hpp"

using namespace std;

// Constructor
// initialize playing and winning hands to empty vectors
// set isOut to false (because they're just starting to play the game)
// initialize numWins to 0
Player::Player() {
    //playingHand = vector<Card>();
    //winningHand = vector<Card>();
    isOut = false;
    numWins = 0;
    handSize = 10;
}

// Methods for War
Card Player::draw_from_playing_hand() {
    // draw top card from the playing hand
    if (playingHand.empty()) {
        cerr << "Error: cannot draw from playing hand because it is empty" << endl;
        return Card(-1, -1); 
    }

    // top of the deck will be considered the last card in the vector (thus pop_back is acceptable)
    Card topCard = playingHand.back();
    // remove top card from playing hand because we we'll be playing this card
    playingHand.pop_back();
    return topCard;
}

void Player::add_to_winning_hand(const vector<Card> addCards) {
    if (addCards.empty()) {
        cerr << "Error: cannot add to winning hand because the input vector is empty" << endl;
        return;
    }

    // append all the cards being added to the current winning hand vector
    winningHand.insert(winningHand.end(), addCards.begin(), addCards.end());
}

void Player::move_winning_to_playing() {
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

// Methods for Trash
void Player::take_turn(vector<Card>& drawPile, vector<Card>& discardPile, vector<double>& traceValues, Player* otherPlayer) {
    Card curCard(-1, -1);

    // TODO
    // check if draw pile is empty and shuffle all cards from discard (except top card) and move to draw pile

    // check if there are any cards in discard pile and if the top card is useful to us
    if (discardPile.size() > 0 && check_need(discardPile[0])) {
        curCard = discardPile[0];
        discardPile.erase(discardPile.begin());
    } 
    // if there are no cards in the discard pile or the top card is not needed, select card from draw pile
    else {
        curCard = drawPile[0];
        drawPile.erase(drawPile.begin());
    }

    // with the current card in hand, check if the card can be swapped with anything in array
    while (check_need(curCard) && !check_showing()) {
        // initialize index to match current card number's index
        int index = curCard.read_numID() - 1;

        // if current card in hand is a jack, run the check algorithm to decide which card in array to swap with jack
        if (curCard.read_charID() == 'J') {
            index = run_jack_algorithm(discardPile, otherPlayer, traceValues);
        } 

        // swap cards
        swap_card(curCard, index);
    }

    // when the current card in hand is useless, add to beginning (top) of discard pile
    discardPile.insert(discardPile.begin(), curCard);
    
}

// checks the current card in hand is a value that can be played with number of cards in array
// checks if the current card value can replace a card that's faced down or slot that currently has a jack
bool Player::check_need(Card& card) {
    // if the card value is within the range of the playingHand size
    if (card.read_numID() < (int)playingHand.size() || card.read_charID() == 'J') { 
        // check each card
        for (Card card : playingHand) { 
            // if our index for that card isn't showing
            if (playingHand[card.read_numID() - 1].read_isShowing() || playingHand[card.read_numID() - 1].read_charID() == 'J') { 
                return true;
            }
        }
    }

    return false;
}

bool Player::check_showing() {
    for (const Card& card : playingHand) {
        if (card.read_isShowing() == false) {
            return false;
        }
    }
    return true;
}

void Player::swap_card(Card& curCard, int index) {
    if (index < 0 || index >= (int)playingHand.size()) {
        cerr << "Error: invalid index for swapping card" << endl;
        return;
    }

    Card tempCard = playingHand[index];
    playingHand[index] = curCard;
    playingHand[index].showCard();
    curCard = tempCard;
}

void Player::empty_hand() {
    playingHand.clear();
}

int Player::run_jack_algorithm(vector<Card>& discardPile, Player* otherPlayer, vector<double>& traceValues) {
    // It's just easiest to reset this everytime I think
    vector<int> jackAlgorithmCounter(playingHand.size(), 0);
    
    // bruh could prolly use a helper function, but I was a nitwit and am now lazy........
    // Check cards in discardPile
    for (Card discardCard: discardPile) {
        if (discardCard.read_numID() < (int)playingHand.size()) {
            jackAlgorithmCounter[discardCard.read_numID() - 1] ++;
        }
    }

    // Check your SHOWING cards
    for (Card yourCard: playingHand) {
        if (yourCard.read_isShowing() && yourCard.read_numID() < (int)playingHand.size()) {
            jackAlgorithmCounter[yourCard.read_numID() - 1] ++;
        }
    }

    // Check your opponent's SHOWING cards
    for (Card otherCard: otherPlayer->read_playing_hand()) {
        if (otherCard.read_isShowing() && otherCard.read_numID() < (int)playingHand.size()) {
            jackAlgorithmCounter[otherCard.read_numID() - 1] ++;
        }
    }

    // Find which card number(s) we have seen the most of, because these are the one's we want to choose from
    vector<int> optimalSpotIndexes;
    // First find max index
    int maxIndex = 0;
    for (int i = 0; i < (int)jackAlgorithmCounter.size(); i ++) {
        // need to check if the card in the array is showing before checking if it's a Jack
        if (playingHand[i].read_isShowing() && playingHand[i].read_charID() == 'J') { // this is necessary for the case of jack being the first card we draw and all of our counters equal 0, then these are not randomly chosen
            jackAlgorithmCounter[i] = -1;
        } else if (jackAlgorithmCounter[i] > jackAlgorithmCounter[maxIndex]) {
            maxIndex = i;
        }
    }

    // Then get all ties
    for (int i = 0; i < (int)jackAlgorithmCounter.size(); i ++) {
        if (jackAlgorithmCounter[i] == jackAlgorithmCounter[maxIndex]) {
            optimalSpotIndexes.push_back(i);
        }
    }

    // Choose randomly from these
    double r = -1;
    int p = -1;

    // if trace values run out, return error
    if (traceValues.empty()) {
        cerr << "Error: not enough trace values for shuffling" << endl;
        exit(1);
    }

    // use trace values for randomness
    r = traceValues[0];
    // remove used trace value
    traceValues.erase(traceValues.begin());

    // select optimal index using the random variable
    p = (int)(r * optimalSpotIndexes.size());
    return optimalSpotIndexes[p];
}

// Mutator (setter) methods
void Player::increment_wins() {
    numWins++;
}

void Player::decrement_handSize() {
    handSize--;
}

void Player::set_isOut(const bool) {
    isOut = true;
}



// Accessor (getter) methods
vector<Card> Player::read_playing_hand() const {
    return playingHand;
}

vector<Card> Player::read_winning_hand() const {
    return winningHand;
}

bool Player::read_isOut() const {
    return isOut;
}

int Player::read_numWins() const {
    if (numWins < 0) {
        cerr << "Error: numWins should never be negative, but it is " << numWins << endl;
    }
    
    return numWins;
}

int Player::read_num_cards() const {
    return playingHand.size() + winningHand.size();
}

int Player::read_handSize() const {
    return handSize;
}