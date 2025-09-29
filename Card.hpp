#ifndef CARD_HPP
#define CARD_HPP

using namespace std;

/*
Class - Card
    Purpose: To encapsulate all identification of a single card into one central object.
    Members
        Private
            - numID (short int): variable
                2-10 = 2-10
                Jack = 11
                Queen = 12
                King = 13
                Ace = 1
            - charID (char): variable
                The primary identifier of the card itself, utilizing the following shorthand.
                2-10 = '2-10'
                Jack = 'J'
                Queen = 'Q'
                King = 'K'
                Ace = 'A'
            - suitID (char): variable
                The classification of the card, utilizing the following shorthand.
                Diamond = 'D'
                Spade = 'S'
                Heart = 'H'
                Club = 'C'

        Public
            - Card(char, string): method
                The inputs of this method correlate respectively and directly to charId and color. This then automatically deducts the numId based on the input charId.
            - read_numID() (short int): method
                Outputs the numID.
            - read_charID() (char): method
                Outputs the charID.
            - read_suitID() (char): method
                Outputs the suitID.
*/
class Card {
private:
    //Variables
    short int numID;
    char charID;
    char suitID;

public:
    //Methods
    Card(char, char);
    short int read_numID() const;
    char read_charID() const;
    char read_suitID() const;

};


#endif