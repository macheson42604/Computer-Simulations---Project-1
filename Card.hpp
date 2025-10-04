#ifndef CARD_HPP
#define CARD_HPP

using namespace std;

/*
Class - Card
    Purpose: To encapsulate all identification of a single card into one central object.
    Menbers
        Private
            - numID (short int): variable
                The value assigned to each card, utilizing the following shorthand.
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
            - Card(char, char): method
                The inputs of this method correlate respectively and directly to charId and suitID. This then automatically deduces the numId based on the input charId.
            - read_numID() (short int): method
                Returns the numID. This is const because nothing should ever be altered in this function.
            - read_charID() (char): method
                Returns the charID. This is const because nothing should ever be altered in this function.
            - read_suitID() (char): method
                Returns the suitID. This is const because nothing should ever be altered in this function.
            - get_value() (int): method
                Returns the value of the card, which is used in game comparisons. This is const because nothing should ever be altered in this function.
                This function translates J, Q, K, A to correct values given the game rules (ex. War: J = 11, Q = 12, K = 13, A = 14)
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

    int get_value() const;
};


#endif