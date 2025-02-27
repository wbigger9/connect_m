#include "connectM.h"
#include <iostream>
using namespace std;

// Constructor
ConnectM::ConnectM(int size, int m) : boardSize(size), M(m) {
    board = new Board(size, m);
}

// Destructor
ConnectM::~ConnectM() {
    delete board;
}

// Handle the human player's turn
void ConnectM::humanTurn() {
    cout << "\nYour turn!" << endl;
    int col;
    cout << "Enter a column number (0-" << boardSize - 1 << "): ";
    cin >> col;

    while (col < 0 || col >= boardSize || !board->placeToken(col, humanToken)) {
        cout << "Invalid move. Enter a column number (0-" << boardSize - 1 << "): ";
        cin >> col;
    }

    board->printBoard();

    // Check if human wins
    if (board->checkForWin(humanToken)) {
        cout << "You win!" << endl;
        exit(0);
    }
}

void ConnectM::computerTurn() {
    cout << "\nComputer's turn!" << endl;
    int col;
    do {
        col = rand() % boardSize; // Pick a random column
    } while (!board->placeToken(col, computerToken)); // Keep trying until a valid move is made}
   
    board->printBoard();

    // Check if computer wins
    if (board->checkForWin(computerToken)) {
        cout << "Computer wins!" << endl;
        exit(0);
    }

}


// Start game loop
void ConnectM::play() {
    board->generateWeightMap();
    board->printBoard();
    while (true) {
        humanTurn();
        computerTurn();
    }
}
