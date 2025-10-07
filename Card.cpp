#include <bits/stdc++.h>

#include "Card.hpp"

using namespace std;

Card::Card(int nID, char sID) {
    numID = nID;
    suitID = sID;

    if (isdigit(cID)) {
        numID = (short int)cID;
    }
}

short int Card::read_numID() const {
    return numID;
}

char Card::read_charID() const {
    return charID;
}

char Card::read_suitID() const {
    return suitID;
}