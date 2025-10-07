#include <bits/stdc++.h>
#include <vector>

#include "Card.hpp"

using namespace std;

Card::Card(int nID, int sID) {
    // set numID
    numID = nID;

    // set charID
    vector<char> faces = ['T', 'J', 'Q', 'K', 'A']
    if (nID > 9) {
        charID = faces[nID % 10];
    } else {
        charID = (char)nID;
    }

    // set suitID
    vector<char> suits = ['D', 'C', 'H', 'S'];
    suitID = suits[sID];
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