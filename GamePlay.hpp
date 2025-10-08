#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

// Creating the hpp file for GamePlay in order to utilize function declarations in other files

// Method Declarations
void setup_war();
void play_war();
vector<Card> make_deck(char);
void shuffle_cards(vector<Card>&);
bool validate_deck(vector<Card>&, char);


#endif