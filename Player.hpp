#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "Card.hpp"

using namespace std;

class Player {
private:
    // Variables
    vector<Card> hand;
    bool skipped;
    int extraDraw;
    bool out;
    Player* nextPlayer;
    bool computer;

public:
    // Methods
    Player(bool);
    vector<Card> read_hand() const;
    bool read_skipped() const;
    int read_extraDraw() const;
    bool read_out() const;
    Player* read_nextPlayer() const;
    void draw_card(Card);
    void set_nextPlayer(Player*);
};

#endif