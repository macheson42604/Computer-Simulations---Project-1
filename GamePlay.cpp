#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>

#include "Card.hpp"
#include "Player.hpp"
#include "GamePlay.hpp"

using namespace std;

/*
 * Coding Style Notes:
 * functions: snake case (should start with a verb)
 * variables: camel case
 */


 // global trace values
 vector<double> traceValues;

/**
 * main(): main function to run both games: War, Trash
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Error: invalid number of arguments. Usage: ./SIM <game type> <trace file>" << endl;
        return 1;
    }

    // gameType (war, trash): determine which game to play
    string gameType = argv[1];
    // traceFile: file containing random numbers for shuffling
    string traceFile = argv[2];

    char gameTypeChar = toupper(gameType[0]);
    if (gameTypeChar != 'W' && gameTypeChar != 'T') {
        cerr << "Error: invalid game type. Valid types are 'War' or 'Trash'" << endl;
        return 1;
    }

    // same trace files for both games into arraylist of doubles
    ifstream traceFileStream(traceFile);
    if (!traceFileStream.is_open()) {
        cerr << "Error: could not open trace file" << endl;
        return 1;
    }
    double value;

    while (traceFileStream >> value) {
        traceValues.push_back(value);
    }

    /*
    output: map<char, int>
        N: Number of turns taken
        T: Number of times the winner has changed
        L: NUMBER when the last winning transition occurred (this needs to be divided by N in the final output)
    */
    map<char, int> outputs { {'N', 0}, {'T', 0}, {'L', 0} };

    // STANDARD SETUP
    // make 2 players
    Player* player1 = new Player();
    Player* player2 = new Player();

    // make deck of cards
    vector<Card> deck = make_deck(gameTypeChar);

    // validate deck of cards 
    if (!validate_deck(deck)) {
        cerr << "Deck initialized incorrectly" << endl;
        return 1;
    };

    // shuffle deck of cards
    // return error if not enough trace values
    if (traceValues.size() < deck.size()) {
        cerr << "Error: not enough trace values for shuffling" << endl;
        return 1;
    }
    shuffle_cards(deck);

    // running Trash
    if (gameTypeChar == 'T') {
        return 0; // TODO: implement Trash
    }
    else if (gameTypeChar == 'W') {
         // running War
        setup_war(player1, player2, deck);
        play_war(outputs, player1, player2);
    }
   
    // output results
    cout << "OUTPUT " << gameType << " turns " << outputs['N'] << " transitions " << outputs['T'] << " last " << outputs['L']/outputs['N'] << endl;
    return 0;
}

void setup_war(Player*& player1, Player*& player2, vector<Card>& deck) {
    // split deck of cards between the two players and set to their playing hands
    vector<Card> deck1(deck.begin(), deck.begin() + 26);
    vector<Card> deck2(deck.begin() + 26, deck.end());


    player1->add_to_winning_hand(deck1); // if erroring, initialize function input outside of function call
    player2->add_to_winning_hand(deck2);

    player1->move_winning_to_playing();
    player2->move_winning_to_playing();


    // Further setup for the War game would go here
}

void play_war(map<char, int>& outputs, Player*& player1, Player*& player2) {
    // create empty vector of tied cards
    vector<Card> tiedCards = vector<Card>();

    int winningPlayer = 0;

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
                //player1->shuffle_winning_hand();
                player1->move_winning_to_playing();
                //player1->clear_winning_hand();
            }
            else {
                player1->set_isOut(true);
            }
        }
        if (player2->read_playing_hand().empty()) {
            if (!player2->read_winning_hand().empty()) {
                //player2->shuffle_winning_hand();
                player2->move_winning_to_playing();
                //player2->clear_winning_hand();
            }
            else {
                player2->set_isOut(true);
            }
        }

        // update outputs
        outputs['N'] ++; // add 1 to turn counter
        // Determine who is currently winning
        int player1CardCount = player1->read_num_cards();
        int player2CardCount = player2->read_num_cards();

        if (player1CardCount > player2CardCount && winningPlayer != 1) {
            outputs['T'] ++; // add 1 to  winning transition counter
            outputs['L'] = outputs['N']; // set last transition equal to the curren turn
            winningPlayer = 1;
        }
        else if (player2CardCount > player1CardCount && winningPlayer != 2) {
            outputs['T'] ++; // add 1 to  winning transition counter
            outputs['L'] = outputs['N']; // set last transition equal to the curren turn
            winningPlayer = 2;
        }
    }


    // if both players are out (tie game - aka all 52 cards somehow are in the tiedCards deck), randomly choose a winning player
    if (player1->read_isOut() && player2->read_isOut()) {
        if (traceValues.empty()) {
            cerr << "Error: not enough trace values for shuffling" << endl;
            exit(1);
        }

        // use trace values for randomness
        double r = traceValues[0];
        // remove used trace value
        traceValues.erase(traceValues.begin());

        if (r > 0.5) {
            player1->increment_wins();
        } else {
            player2->increment_wins();
        }

        // VALIDATION CHECK - all cards should now be in tied pile
        validate_deck(tiedCards);
    }

    // player 2 is out, player 1 is not
    else if (!player1->read_isOut() && player2->read_isOut()) {
        player1->increment_wins();

        // VALIDATION CHECK - all cards should now be in player 1's hand
        vector<Card> p1Hand = player1->read_playing_hand();
        vector<Card> p1WHand = player1->read_winning_hand();

        p1Hand.insert(p1Hand.end(), p1WHand.begin(), p1WHand.end());

        validate_deck(p1Hand);
    }
    // player 1 is out, player 2 is not
    else if (player1->read_isOut() && !player2->read_isOut()) {
        player2->increment_wins();

        // VALIDATION CHECK - all cards should now be in player 2's hand
        vector<Card> p2Hand = player2->read_playing_hand();
        vector<Card> p2WHand = player2->read_winning_hand();

        p2Hand.insert(p2Hand.end(), p2WHand.begin(), p2WHand.end());

        validate_deck(p2Hand);
    }
}

vector<Card> make_deck(char gameType) {
    // create standard deck of 52 cards
    vector<Card> deck = vector<Card>();

    if (gameType == 'W') {
        for (int suit = 0; suit < 4; suit ++) {
        for (int value = 2; value <= 14; value ++) { // where Ace = 14
            deck.push_back(Card(value, suit));
        }
    }
    }
    else if (gameType == 'T') {
        for (int suit = 0; suit < 4; suit ++) {
            for (int value = 2; value <= 14; value ++) { // where Ace = 1
                Card card = Card(value, suit);
                if (value == 14) {
                    card.set_numID(1);
                }
                deck.push_back(card);
            }
        }
    }
    else {
        cerr << "Error: invalid game type input to make_deck function" << endl;
        return vector<Card>();
    }
    
    return deck;
}

/**
 * shuffles deck of cards at beginning of round
 * War: shuffles winning hand before moving to playing hand 
 */
void shuffle_cards(vector<Card>& cards) {
    double r = -1;
    int p = -1;

    for (int c = 0; c < (int)cards.size(); c ++) {
        // if trace values run out, return error
        if (traceValues.empty()) {
            cerr << "Error: not enough trace values for shuffling" << endl;
            exit(1);
        }

        // use trace values for randomness
        r = traceValues[0];
        // remove used trace value
        traceValues.erase(traceValues.begin());
        p = (r * (cards.size() - c)) + c;
        
        // Swap Cards
        Card copyCard = cards[p]; // temporary duplicate card
        cards[p] = cards[c];
        cards[c] = copyCard;
    }
}

bool validate_deck(vector<Card>& deck) {
    bool valid = true;
    if (deck.size() != 52) { // size check
        cerr << "Error: invalid deck size" << endl;
        valid = false;
    }

    // Validation Check: one of each card
    vector<char> suits = {'D', 'C', 'H', 'S'};
    // Run through every possible card value
    for (int suitIndex = 0; suitIndex < 4; suitIndex ++) {
        for (int value = 2; value <= 14; value ++) {
            int cardCounter = 0;
            Card invalidCard = deck[0];
            
            // Now check each of those possibilities against the cards in our deck
            for (Card card : deck) {
                if (value == 14) { // this if statement checks for 1 or 14 to account for the differing Ace values
                    if ( ((card.read_numID() == 14) || card.read_numID() == 1) && (card.read_suitID() == suits[suitIndex]) ) {
                        cardCounter ++;
                        invalidCard = card;
                    }
                } else if ( (card.read_numID() == value) && (card.read_suitID() == suits[suitIndex]) ) { // all other cards besides Ace
                    cardCounter ++;
                    invalidCard = card;
                }
            }

            if (cardCounter != 1) {
                cerr << "Error: invalid card count - " << invalidCard.read_suitID() << invalidCard.read_numID() << " has a counter of " << cardCounter << endl;
                valid = false;
            } // if cardCounter
        } // for numID values
    } // for suitID values

    return valid;
}