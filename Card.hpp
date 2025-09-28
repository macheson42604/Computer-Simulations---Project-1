#ifndef CARD_HPP
#define CARD_HPP

#include<string>

using namespace std;

/*
Class - Card
    Purpose: To encapsulate all identification of a single card into one central object.
    Members
        Private
            - numID (short int): variable
                For all standard numbered cards (0-9) this var will reflect the typical number. Non-standard cards (Reverse, Wild, +2, +4 Wild, & Skip) with automatically be considered -1. This is automatically set in the Card() consutructor based on the input charId;
            - charID (char): variable
                The primary identifier of the card itself, utilizing the following shorthand.
                0-9 = 0-9
                Reverse = R
                Skip = S
                Wild = W
                +4 Wild = F (for four)
                +2 = T (for two)
            - colorID (string): variable
                The secondary identifier of the card itself. All colors will be spelled out in full english (red, yellow, green, or blue).
        Public
            - Card(char, string): method
                The inputs of this method correlate respectively and directly to charId and color. This then automatically deducts the numId based on the input charId.
            - read_numID() (short int): method
                Outputs the numID.
            - read_charID() (char): method
                Outputs the charID.
            - read_colorID() (string): method
                Outputs the colorID.
*/
class Card {
private:
    //Variables
    short int numID;
    char charID;
    string colorID;

public:
    //Methods
    Card(char, string);
    short int read_numID() const;
    char read_charID() const;
    string read_colorID() const;
};


#endif