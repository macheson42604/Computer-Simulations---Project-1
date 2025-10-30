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

// --------------------------------------------------------------------------------------------
// METHODS FOR WAR
// --------------------------------------------------------------------------------------------

Card Player::draw_from_playing_hand() {
    // draw top card from the playing hand
    if (playingHand.empty()) {
        cerr << "Error: cannot draw from playing hand because it is empty" << endl;
        exit(1); 
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



// --------------------------------------------------------------------------------------------
// METHODS FOR TRASH
// --------------------------------------------------------------------------------------------

void Player::take_turn(vector<Card>& drawPile, vector<Card>& discardPile, Player* otherPlayer) {
    Card curCard(-1, -1);

    // TODO
    // check if draw pile is empty and shuffle all cards from discard (except top card) and move to draw pile
    /* "If the draw pile is depleted at the beginning of a turn, the discard pile (except for the top-most, "showing" card) is shuffled to become the new draw pile. 
    The discard pile retains the top-most card, which is from the end of the other player's last turn."
    */
    if (drawPile.size() == 0) {
        move_discard_to_draw(discardPile, drawPile);
    }

    // check if there are any cards in discard pile and if the top card is useful to us
    if (discardPile.size() > 0 && check_need(discardPile[0])) {
        curCard = discardPile[0];
        discardPile.erase(discardPile.begin());
    } 
    // if there are no cards in the discard pile or the top card is not needed, select card from draw pile
    else if (drawPile.size() > 0) {        
        curCard = drawPile[0];
        drawPile.erase(drawPile.begin());
    }
    else {
        cerr << "Error: both draw pile and discard pile are empty when trying to take a turn" << endl;
        exit(1);
    }
    
    // with the current card in hand, check if the card can be swapped with anything in array
    while (check_need(curCard)) {
        // DEBUG
        cout << "Current Card in Hand: " << curCard.read_numID() << " " << curCard.read_suitID() << endl;


        // if all cards in array haven't been flipped up yet, continue to flip
        if (!check_showing()) {
             // initialize index to match current card number's index
            int index = curCard.read_numID() - 1;

            // if current card in hand is a jack, run the check algorithm to decide which card in array to swap with jack
            if (curCard.read_charID() == 'J') {
                index = run_jack_algorithm(discardPile, otherPlayer);
            } 

            // swap cards
            swap_card(curCard, index);
        }
        
        // if all cards in array have been flipped to showing, reshuffle hand only for this player with a decremented array size
        else {
            // keep holding current card (do not include this in the reshuffle)
            // combine this player's array, discard pile, draw pile
            // place all in draw pile to make seting player hand easier
            drawPile.insert(drawPile.begin(), discardPile.begin(), discardPile.end());
            discardPile.clear();
            drawPile.insert(drawPile.begin(), playingHand.begin(), playingHand.end());
            empty_hand();
            // set all cards to not showing and shuffle
            for (Card& card: drawPile) { card.set_not_showing(); }
            shuffle_cards(drawPile);

            // decrement playing hand array size
            decrement_handSize();
            // break out of while loop if the player has won
            if (handSize == 0) { return; }

            // redistribute playing hand array & rest in draw pile
            set_player_hand(drawPile);
        }
       
    }

    // when the current card in hand is useless, add to beginning (top) of discard pile
    discardPile.insert(discardPile.begin(), curCard);
    
}

// read hand size of player and distribute from drawPile, keeping rest in drawPile
void Player::set_player_hand(vector<Card>& drawPile) {
    if ((int)drawPile.size() < handSize) {
        cerr << "Error: not enough cards in draw pile to set player hand" << endl;
        exit(1);
    }
    if (handSize <= 0) {
        cerr << "Error: cannot set player hand because hand size is less than or equal to 0" << endl;
        exit(1);
    }

    // take top cards from draw pile to set as player's playing hand
    playingHand.insert(playingHand.end(), drawPile.begin(), drawPile.begin() + handSize);
    drawPile.erase(drawPile.begin(), drawPile.begin() + handSize);
}


// checks the current card in hand is a value that can be played with number of cards in array
// checks if the current card value can replace a card that's faced down or slot that currently has a jack
bool Player::check_need(Card& card) {
    // if card is a jack, check if any valid positions to place jack
    // can use a jack if there is at least 1 spot that is not showing (do not use on a card that's already a jack)
    if (card.read_charID() == 'J') {
        for (int i = 0; i < (int)playingHand.size(); i++) {
            if (!playingHand[i].read_isShowing()) {
                return true;
            }
        }
        // no valid positions for Jack (all cards are showing)
        return false;
    }

    // if the card value is within the range of the playingHand size 
    if (card.read_numID() < 1) {
        cout << "Error: invalid card number ID in check_need" << endl;
        exit(1);
    }
    if (card.read_numID() <= (int)playingHand.size()) { 
        // check if the card at that index is not showing or is a jack
        if (!playingHand[card.read_numID() - 1].read_isShowing() || playingHand[card.read_numID() - 1].read_charID() == 'J') { 
            return true;
        }
    }
    
    return false;
}

bool Player::check_showing() {
    if (playingHand.empty()) {
        cerr << "Error: cannot check showing because playing hand is empty" << endl;
        exit(1);
    }
    
    for (const Card& card : playingHand) {
        if (card.read_isShowing() == false) {
            return false;
        }
    }
    return true;
}


void Player::add_to_playing_hand(const vector<Card> addCards) {
    if (addCards.empty()) {
        cerr << "Error: cannot add to playing hand because the input vector is empty" << endl;
        return;
    }

    // append all the cards being added to the current playing hand vector
    playingHand.insert(playingHand.end(), addCards.begin(), addCards.end());
}

void Player::move_discard_to_draw(vector<Card>& discardPile, vector<Card>& drawPile) {
    if (discardPile.size() <= 1) {
        cerr << "Error: cannot move discard to draw because there are not enough cards in discard pile" << endl;
        exit(1);
    }
    // reserve the top card from the discard pile
    Card topDiscard = discardPile[0];
    discardPile.erase(discardPile.begin());

    // shuffle rest of cards in discard pile and set all the cards to not showing
    // add reference to modify original cards in discardPile
    shuffle_cards(discardPile);
    for (Card& card : discardPile) {
        card.set_not_showing();
    }

    // move shuffled cards from discard to draw
    drawPile.insert(drawPile.end(), discardPile.begin(), discardPile.end());

    // erase all cards from discardPile and add top discard pile card
    discardPile.clear();
    discardPile.insert(discardPile.begin(), topDiscard);

}

void Player::swap_card(Card& curCard, int index) {
    // check if index given is out of bounds
    if (index < 0 || index >= (int)playingHand.size()) {
        cerr << "Error: invalid index for swapping card" << endl;
        exit(1);
    }

    // create third temporary card
    Card tempCard = playingHand[index];
    // place card in hand into given index in array and set card to be showing
    playingHand[index] = curCard;
    playingHand[index].showCard();
    // take the card from the array to be new card in hand (this card could be set as showing or not showing)
    curCard = tempCard;
    // set current card in hand to not showing
    curCard.set_not_showing();
}

void Player::empty_hand() {
    playingHand.clear();
}

int Player::run_jack_algorithm(vector<Card>& discardPile, Player* otherPlayer) {
    // It's just easiest to reset this everytime I think
    vector<int> jackAlgorithmCounter(playingHand.size(), 0);
    
    // bruh could prolly use a helper function, but I was a nitwit and am now lazy........
    // Check cards in discardPile
    for (Card discardCard: discardPile) {
        if (discardCard.read_numID() >= 1 && discardCard.read_numID() <= (int)playingHand.size()) {
            jackAlgorithmCounter[discardCard.read_numID() - 1] ++;
        }
    }

    // Check your SHOWING cards
    for (Card yourCard: playingHand) {
        if (yourCard.read_isShowing() && yourCard.read_numID() >= 1 && yourCard.read_numID() <= (int)playingHand.size()) {
            jackAlgorithmCounter[yourCard.read_numID() - 1] ++;
        }
    }

    // Check your opponent's SHOWING cards
    for (Card otherCard: otherPlayer->read_playing_hand()) {
        if (otherCard.read_isShowing() && otherCard.read_numID() >= 1 && otherCard.read_numID() <= (int)playingHand.size()) {
            jackAlgorithmCounter[otherCard.read_numID() - 1] ++;
        }
    }

    // Exclude positions that can't be replaced (cards that are already showing and in the correct position)
    for (int i = 0; i < (int)jackAlgorithmCounter.size(); i ++) {
        // need to check if the card in the array is showing before checking if it's a Jack
        // this is necessary for the case of jack being the first card we draw and all of our counters equal 0, then these are not randomly chosen
        if (playingHand[i].read_isShowing() && (playingHand[i].read_charID() == 'J' || playingHand[i].read_numID() == i+1)) { 
            jackAlgorithmCounter[i] = -1;
        } 
    }

    // Find which card number(s) we have seen the most of, because these are the one's we want to choose from
    vector<int> optimalSpotIndexes;
    // First find max index
    int maxIndex = -1;
    int maxValue = -1;
    for (int i = 0; i < (int)jackAlgorithmCounter.size(); i ++) {
        // excluding marked indices with -1 values
        if (jackAlgorithmCounter[i] != -1 && jackAlgorithmCounter[i] > maxValue) {
            maxIndex = i;
            maxValue = jackAlgorithmCounter[i];
        }
    }

    if (maxIndex == -1) {
        cerr << "Error: maxIndex was not updated in jack algorithm" << endl;
        exit(1);
    }

    // Then get all ties
    // This will result in optimalSpotIndexes ALWAYS having at least 1 value in vector
    for (int i = 0; i < (int)jackAlgorithmCounter.size(); i ++) {
        if (jackAlgorithmCounter[i] == maxValue) {
            optimalSpotIndexes.push_back(i);
        }
    }

    // If there's only 1 optimal spot, immediately select it
    if (optimalSpotIndexes.size() == 1) {
        return optimalSpotIndexes[0];
    }

    // Choose randomly from these
    double r = -1;
    int p = -1;

    // if trace values run out, return error
    /*if (traceValues.empty()) {
        cerr << "Error: not enough trace values for shuffling" << endl;
        exit(1);
    }*/

    // use trace values for randomness
    r = get_traceValue(); // traceValues[0];
    // remove used trace value
    //traceValues.erase(traceValues.begin());

    // select optimal index using the random variable
    p = (int)(r * optimalSpotIndexes.size());
    return optimalSpotIndexes[p];
}

int Player::calc_num_from_winning() {
    /*
    In Trash we decide who is winning by determining who has the smallest number of array slots to fill before the game ends. 
    Calculate remaining number of arrays we need to cover (each array size: 1, 2, ..., n) = (n+1)n/2
    Calculate remaining number of cards that need to be showing in current array
    Sum for remaining number of cards that need to be showing to win game
    */

    // use current handSize
    int remainArrs = handSize - 1;

    // remaining cards in current array to show
    int remainShow = 0;
    for (const Card& card: playingHand) {
        if (!card.read_isShowing()) {remainShow ++;}
    }

    // sum remaining num cards
    return ((remainArrs + 1) * remainArrs / 2) + remainShow;
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