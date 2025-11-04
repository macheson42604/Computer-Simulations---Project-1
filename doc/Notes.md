# GRADING INFO
- Fisher-Yates: `GamePlay.cpp` `shuffle_card(vector<Card>& cards)` function - line 394
- Trash Player Hand Function: `Player.cpp` `take_turn(vector<Card>& drawPile, vector<Card>& discardPile, Player* otherPlayer)` function - line 84


# Misc. Notes
## Testing 
Create a test file
- `/SIMGRADING/Random 423 | head -n 30000 >tests/test.dat`

Run test file
- `./SIM war ./tests/test.dat`

## Grading (Graphs)
- `~/tmp/War-and-Trash/grader.sh`
- `~/tmp/War-and-Trash/grader.sh . 2000`