#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>
using namespace std;

class Board {
private:
    int boardSize;
    int M;
    char** board; // Dynamic 2D array
    int recentCol;
    int recentRow;
    int** weightMap; // Dynamic 2D array
public:
    Board(int size, int m);
    ~Board();
    
    void printBoard();
    bool placeToken(int col, char token); // Places a token in the lowest available row
    void removeToken(); // Removes a the top token in a column
    bool checkForWin(char token); // Checks for a win using recent move
    int countConsecutive(char plane[], int size, char token, int M); // Count consecutive tokens

    void generateWeightMap();
    int setWeight(int row, int col) const;

    // helper functions for adversarial search
    bool canPlaceToken(int col);                                // returrns true if a token can be placed in the column
    int removeToken(int col);                                   // removes the top-most token in the given column and returns its row incdex
    bool isFull();                                              // returns true if the board is completely full
    int evaluate(char computerToken, char humanToken);          // heuristic evaluation function
    bool isTerminalState(char computerToken, char humanToken);  // checks if the game is over (win or draw)

    // Getters
    int getWeight(int row, int col);

    char** getBoard() { return board; }
    int getSize() { return boardSize; }
    int getRecentCol() { return recentCol; }
    int getRecentRow() { return recentRow; }
};

#endif
