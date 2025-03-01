# connect_m

Authors: William Bigger, Brennan Thompson

ConnectM is a board game similar to Connect 4 but with variable-length board sizes and M values
(the number of consecutive pieces needed to win).
The AI uses min-maxing with alpha-beta pruning. It also uses a heuristic function.
The heuristic includes the weight map, which assigns a score to each board position,
prioritizes winning moves, and prioritizes blocking human winning moves.

To run, type : 
make clean && make 
./connectM N M H
where:
N = board size
M = consecutive pieces to win
H = 0 (computer goes first) || H = 1 (human goes first)