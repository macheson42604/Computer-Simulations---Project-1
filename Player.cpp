#include "Player.hpp"

using namespace std;

Player::Player() {
    out = false;
}

vector<Card> Player::read_hand() const {
    return hand;
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

void Player::set_nextPlayer(Player* nPlayer) {
    nextPlayer = nPlayer;
}