#include <cstring>
#include <bits/stdc++.h>

#include "Card.hpp"

using namespace std;

Card::Card(char chID, string coID) {
    charID = chID;
    colorID = coID;

    if (isdigit(chID)) {
        numID = (short int)chID;
    }
}

short int Card::read_numID() const {
    return numID;
}

char Card::read_charID() const {
    return charID;
}

string Card::read_colorID() const {
    return colorID;
}