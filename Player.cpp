#include "Player.hpp"

using namespace std;

Player::Player(bool comp) {
    skipped = false;
    out = false;
    extraDraw = 0;
    computer = comp;
}

vector<Card> Player::read_hand() const {
    return hand;
}

bool Player::read_skipped() const {
    return skipped;
}

int Player::read_extraDraw() const {
    return extraDraw;
}

bool Player::read_out() const {
    return out;
}

Player* Player::read_nextPlayer() const {
    return nextPlayer;
}

void Player::draw_card(Card newCard) {
    hand.push_back(newCard);
}

void Player:: set_nextPlayer(Player* next) {

}