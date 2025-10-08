#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib>
#include <vector>

#include "Card.hpp"
#include "Player.hpp"

using namespace std;

/*
 * Coding Style Notes:
 * functions: snake case (should start with a verb)
 * variables: camel case
 */





/**
 * main(): main function to run both games: War, Trash
 */
int main() {
    // running War
    setup_war();
    play_war();

    // game_setup();

    return 0;
}

void setup_war() {
    // make 2 players
    Player* player1 = new Player("Player 1");
    Player* player2 = new Player("Player 2");

    // make deck of cards
    vector<Card> deck = make_deck();

    // validate deck of cards 
    validate_deck(deck*);

    // shuffle deck of cards
    shuffle_deck(deck*);

    // split deck of cards between the two players and set to their playing hands
    player1.add_to_winning_hand(new vector<Card> (deck.begin(), deck.begin() + 26)); // if erroring, initialize function input outside of function call
    player2.add_to_winning_hand(new vector<Card> (deck.begin() + 26, deck.end()));


    // Further setup for the War game would go here
}

void play_war() {
    // create empty vector of tied cards
    vector<Card> tiedCards = new vector<Card>();

    // loop until at least one of the players is out of cards
    while (!player1->read_isOut() && !player2->read_isOut()) {
        // each player draws the top card from their playing hand
        Card card1 = player1->draw_from_playing_hand();
        Card card2 = player2->draw_from_playing_hand();

        // compare the cards and determine the winner of the round
        // player 1 wins the round
        if (card1.read_numID() > card2.read_numID()) {
            // first add neutral cards to the winner's winning hand
            if (!tiedCards.empty()) {
                player1->add_to_winning_hand(tiedCards);
                // clear the tiedCards vector
                tiedCards.clear();
            }
            // add the winning cards to the winner's winning hand
            // add player 1's card first, then player 2's card
            player1->add_to_winning_hand({card1, card2});
        }

        // player 2 wins the round
        else if (card2.read_numID() > card1.read_numID()) {
             // first add neutral cards to the winner's winning hand
            if (!tiedCards.empty()) {
                player2->add_to_winning_hand(tiedCards);
                // clear the tiedCards vector
                tiedCards.clear();
            }
            // add the winning cards to the winner's winning hand
            // add player 2's card first, then player 1's card
            player2->add_to_winning_hand({card2, card1});
        }

        // players tie the round
        else {
            // add both cards to the tiedCards vector (order doesn't matter)
            tiedCards.push_back(card1);
            tiedCards.push_back(card2);
        }

        // check if either player is out of cards (check both playing and winning hands)
        if (player1->read_playing_hand().empty()) {
            if (!player1->read_winning_hand().empty()) {
                player1->shuffle_winning_hand();
                player1->move_winning_to_playing();
                player1->clear_winning_hand();
            }
            else {
                player1->set_isOut(true);
            }
        }
        if (player2->read_playing_hand().empty()) {
            if (!player2->read_winning_hand().empty()) {
                player2->shuffle_winning_hand();
                player2->move_winning_to_playing();
                player2->clear_winning_hand();
            }
            else {
                player2->set_isOut(true);
            }
        }
    }

    // TODO
    // validate deck of cards (should be all 52 cards accounted for between both players' playing and winning hands, and the tiedCards vector)
    // correct number and suits of cards
    // vector<Card> allCards;
    // allCards.validate_deck();

    // if both players are out (tie game - aka all 52 cards somehow are in the tiedCards deck), no player earns a point
    // player 2 is out, player 1 is not
    if (!player1->read_isOut() && player2->read_isOut()) {
        player1->increment_wins();
    }
    // player 1 is out, player 2 is not
    else if (player1->read_isOut() && !player2->read_isOut()) {
        player2->increment_wins();
    }
}

vector<Card> make_deck() {
    vector<Card> deck;
    
    for (int suit = 0; suit < 4; suit ++) {
        for (int value = 2; value <= 14; value ++) { // where 14 is the Ace
            deck.push_back(Card(value, suit));
        }
    }
}

/**
 * shuffles deck of cards at beginning of round
 * War: shuffles winning hand before moving to playing hand 
 */
void shuffle_cards(vector<Card>& cards) {
    double r = -1;
    int p = -1;

    for (int c = 0; c < cards.size(); c ++) {
        // TO DO:
        // Add trace file
        // set r to a trace file value
        r = rand(); // CHANGE TO PULL FROM TRACE FILE
        p = (r * (cards.size() - c)) + c;
        
        // Swap Cards
        Card copyCard = cards[p]; // temporary duplicate card
        cards[p] = cards[c];
        cards[c] = copyCard;
    }
}

bool vaildate_deck(vector<Card>& deck) {
    bool valid = true;

    // Validation Check: size of deck
    if (deck.size() != 52) {
        cout << "Error: invalid deck size" << endl;
        valid = false;
    }

    // Validation Check: one of each card
    Card invalid = null;
    vector<char> suits = ['D', 'C', 'H', 'S'];
    // Run through every possible card value
    for (int suitIndex = 0; suitIndex < 4; suitIndex ++) {
        for (int value = 2; value < 14; value ++) {
            int cardCounter = 0;
            
            // Now check each of those possibilities against the cards in our deck
            for (Card card : deck) {
                if ( (card.read_numID() == value) && (card.read_suitID() == suits[suitIndex]) ) {
                    cardCounter ++;
                    invalidCard = card;
                }
            }

            if (cardCounter != 1) { // checks both too many and too few
                cout << "Error: invalid card count - " << card.read_suitID() << card.read_numID() << " has a counter of " << cardCounter << endl;
                valid = false;
            } // if cardCounter
        } // for numID values
    } // for suitID values

    if (!valid) { // if invalid deck, display all cards for troubleshooting
        for (int i = 0; i < deck.size(); i ++) {
            cout << i << ") " << deck[i].read_charID() << ", " << deck[i].read_suitID() << endl;
        }
    }

    return valid;
}