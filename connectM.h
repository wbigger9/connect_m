#ifndef CONNECTM_H
#define CONNECTM_H

#include "board.h"

class ConnectM {
private:
    int boardSize;
    int M;
    Board* board;
    char humanToken = 'X';
    char computerToken = 'O';
    // minimax with alpha-beta pruning
    int minimax(int deptj, int alpha, int beta, bool maximizingPlayer);
    bool humanFirst;  // ✅ Track if human goes first

public:
ConnectM(int size, int m, bool humanFirst);

~ConnectM();
    
    void humanTurn();
    void computerTurn();
    void play();
};

#endif
