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

public:
    ConnectM(int size, int m);
    ~ConnectM();
    
    void humanTurn();
    void computerTurn();
    void play();
};

#endif
