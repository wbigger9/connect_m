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

// minmax function with alpha-beta pruning
int ConnectM::minimax(int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0 || board->isTerminalState(computerToken, humanToken)) {
        return board->evaluate(computerToken, humanToken);
    }

    if (maximizingPlayer) {
        int maxEval = -1000000;
        for (int col = 0; col < boardSize; col++) {
            if (board->canPlaceToken(col)) {
                board->placeToken(col, computerToken);
                int eval = minimax(depth - 1, alpha, beta, false);
                board->removeToken(col);
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 1000000;
        for (int col = 0; col < boardSize; col++) {
            if (board->canPlaceToken(col)) {
                board->placeToken(col, humanToken);
                int eval = minimax(depth - 1, alpha, beta, true);
                board->removeToken(col);
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return minEval;
    }
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
    int bestScore = -1000000;
    int bestMove = -1;
    int searchDepth = 4; // Adjust this value to control the depth of the search
    // int col;

    for (int col = 0; col < boardSize; col++) {
        if (board->canPlaceToken(col)) {
            board->placeToken(col, computerToken);
            int score = minimax(searchDepth, -1000000, 1000000, false);
            board->removeToken(col);
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
            }
        }
    }

    if (bestMove != -1) {
        board->placeToken(bestMove, computerToken);
        cout << "Computer places token in column " << bestMove << endl;
    } else {
        cout << "No moves left! Draw." << endl;
        exit(0);
    }
   
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
    cout << "Board printed. Waiting for your move..." << endl;  // Debug print
    while (true) {
        humanTurn();
        computerTurn();
    }
}
