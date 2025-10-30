#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include <map>
#include <vector>
#include "Card.hpp"
#include "Player.hpp"

// Creating the hpp file for GamePlay in order to utilize function declarations in other files

// Method Declarations
// War
void setup_war(Player*&, Player*&, vector<Card>&);
void play_war(map<char, int>&, Player*&, Player*&);

// Trash
void setup_trash(Player*& , Player*& , vector<Card>&);
void play_trash(map<char, int>&, Player*& , Player*& , vector<Card>&);
void update_trash_stats(map<char, int>&, Player*&, Player*&, int&);

// Additional Helpers
vector<Card> make_deck(char);
void shuffle_cards(vector<Card>&);
bool validate_deck(vector<Card>&);
double get_traceValue();

#endif