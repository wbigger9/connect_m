#include "board.h"
#include <cmath>

// Constructor
Board::Board(int size, int m) : boardSize(size), M(m), recentCol(-1), recentRow(-1), weightMap(nullptr) {
    board = new char*[boardSize];
    for (int i = 0; i < boardSize; i++) {
        board[i] = new char[boardSize];
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = ' '; // Initialize empty spaces
        }
    }
}

// Destructor
Board::~Board() {
    for (int i = 0; i < boardSize; i++) {
        delete[] board[i];
    }
    delete[] board;

        // ✅ Free weightMap if it was allocated
        if (weightMap) {
            for (int i = 0; i < boardSize; i++) {
                delete[] weightMap[i];
            }
            delete[] weightMap;
        }
}

void Board::printBoard() {
    // 1️⃣ Print the Weight Map
    cout << "\nWeight Map:\n";
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            cout << " " << weightMap[i][j] << " ";  // Display weight
            if (j < boardSize - 1) cout << "|"; // Vertical separator
        }
        cout << endl;

        if (i < boardSize - 1) { // Horizontal separator
            for (int j = 0; j < boardSize; j++) {
                cout << "---";
                if (j < boardSize - 1) cout << "+";
            }
            cout << endl;
        }
    }

    // 2️⃣ Print the Game Board
    cout << "\nGame Board:\n";
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            cout << " " << board[i][j] << " ";  // Display token (or empty)
            if (j < boardSize - 1) cout << "|"; // Vertical separator
        }
        cout << endl;

        if (i < boardSize - 1) { // Horizontal separator
            for (int j = 0; j < boardSize; j++) {
                cout << "---";
                if (j < boardSize - 1) cout << "+";
            }
            cout << endl;
        }
    }
}



// Place a token into the lowest available row in the column
bool Board::placeToken(int col, char token) {
    if (col < 0 || col >= boardSize) return false;

    for (int i = boardSize - 1; i >= 0; i--) {
        if (board[i][col] == ' ') {
            board[i][col] = token;
            recentCol = col;
            recentRow = i;
            return true;
        }
    }
    return false; // Column full
}

// Remove the top token from a column
void Board::removeToken() {
    if (board[recentRow][recentCol] != ' ') {
        board[recentRow][recentCol] = ' ';
    }
}

// Count the number of consecutive tokens in a row
int Board::countConsecutive(char plane[], int size, char token, int M) {
    int count = 0;  // Track consecutive occurrences

    for (int i = 0; i < size; i++) {
        if (plane[i] == token) {
            count++;  
            if (count == M) {  // If we reach M in a row, return M
                return M;
            }
        } else {
            count = 0;  // Reset count if sequence breaks
        }
    }

    return 0;  // No winning streak found
}

// Check if a player has won using recent move
bool Board::checkForWin(char token) {
    if (recentRow == -1 || recentCol == -1) return false; // No move has been made yet

    vector <char> horizontalPlane(boardSize);
    vector <char> verticalPlane(boardSize);
    // 🔹 Extract Horizontal Plane
    for (int i = 0; i < boardSize; i++) {
        horizontalPlane[i] = board[recentRow][i];
    }
    if (countConsecutive(horizontalPlane.data(), horizontalPlane.size(), token, M) >= M) {
        return true;
    }

    // 🔹 Extract Vertical Plane
    for (int i = 0; i < boardSize; i++) {
        verticalPlane[i] = board[i][recentCol];
    }
    if (countConsecutive(verticalPlane.data(), verticalPlane.size(), token, M) >= M) {
        return true;
    }


   // 🔹 Extract Diagonal Plane (\ direction)
vector<char> diagonalPlane;

// Step 1: Move to **top-left (↖) boundary** of the diagonal
int diagonalRow = recentRow;
int diagonalCol = recentCol;
while (diagonalRow > 0 && diagonalCol > 0) { 
    diagonalRow--;  // Move up
    diagonalCol--;  // Move left
}

// Step 2: Collect diagonal elements moving **down-right (↘)**
while (diagonalRow < boardSize && diagonalCol < boardSize) { 
    diagonalPlane.push_back(board[diagonalRow][diagonalCol]);
    diagonalRow++;  // Move down
    diagonalCol++;  // Move right
}

// Step 3: Check for a winning sequence in the diagonal
if (countConsecutive(diagonalPlane.data(), diagonalPlane.size(), token, M) >= M) {
    return true;
}



      // 🔹 Extract Anti-Diagonal Plane    
vector<char> antiDiagonalPlane;

// Step 1: Move to **top-right (↗) boundary** of the anti-diagonal
int antiDiagonalRow = recentRow;
int antiDiagonalCol = recentCol;

while (antiDiagonalRow > 0 && antiDiagonalCol < boardSize - 1) {
    antiDiagonalRow--;  // Move up
    antiDiagonalCol++;
}

// Step 2: Collect anti-diagonal elements moving **down-left (↙)**
while (antiDiagonalRow < boardSize && antiDiagonalCol >= 0) {
    antiDiagonalPlane.push_back(board[antiDiagonalRow][antiDiagonalCol]);
    antiDiagonalRow++;  // Move down
    antiDiagonalCol--;  // Move left
}
if (countConsecutive(antiDiagonalPlane.data(), antiDiagonalPlane.size(), token, M) >= M) {
    return true;
}


    return false;
}

// Generate a weight map for each cell
void Board::generateWeightMap() {
        // ✅ Free weightMap if it was allocated
        if (weightMap) {
            for (int i = 0; i < boardSize; i++) {
                delete[] weightMap[i];
            }
            delete[] weightMap;
        }

    weightMap = new int*[boardSize];
    for (int i = 0; i < boardSize; i++) {
        weightMap[i] = new int[boardSize];
        for (int j = 0; j < boardSize; j++) {
            weightMap[i][j] = setWeight(i, j);
        }
    }

}

// Set the weight of a cell based on its position
// Set the weight of a cell based on its position
int Board::setWeight(int row, int col) const {
    
    // 1️⃣ Correct middle column calculation
    double middleCol = (boardSize - 1) / 2.0;  // ✅ Center correctly between two middle cols for even board sizes
    
    // 2️⃣ Calculate distance from the middle
    double distanceFromMiddle = abs(col - middleCol);

    // 3️⃣ Calculate distance from the bottom
    int distanceFromBottom = (boardSize - 1) - row;

    // 4️⃣ Define weight scaling factors
    double middleScaling = 2.0;  // ✅ Stronger preference for center
    double bottomScaling = 1.5;  // ✅ Still favors lower positions

    // 5️⃣ Compute final weight
    int weight = round(30 - (middleScaling * distanceFromMiddle) - (bottomScaling * distanceFromBottom));

    // 6️⃣ Ensure weight is non-negative
    return max(1, weight);
}

// get the weight of a cell
int Board::getWeight(int row, int col) {
    return weightMap[row][col];
}

// returns true if a token can be placed in the column
bool Board::canPlaceToken(int col) {
    if (col < 0 || col >= boardSize) return false;
    return board[0][col] == ' ';
}

// removes the top-most token in the given column and returns its row index
int Board::removeToken(int col) {
    for (int i = boardSize - 1; i >= 0; i--) {
        if (board[i][col] != ' ') {
            board[i][col] = ' ';
            return i;
        }
    }
    return -1; // if column is empty
}

// checks if the board is full
bool Board::isFull() {
    for (int i = 0; i < boardSize; i++) {
        if (board[0][i] == ' ') {
            return false;
        }
    }
    return true;
}

// heuristic evaluation function
// returns +10000 if computer wins, -10000 if player wins, otherwise uses the weight map to evaluate the board advantage
int Board::evaluate(char computerToken, char humanToken) {
    if (checkForWin(computerToken)) return 10000;
    if (checkForWin(humanToken)) return -10000;
    int score = 0;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == computerToken) {
                score += weightMap[i][j];
            } else if (board[i][j] == humanToken) {
                score -= weightMap[i][j];
            }
        }
    }
    return score;
}

// check if game is over (win or draw)
bool Board::isTerminalState(char computerToken, char humanToken) {
    return checkForWin(computerToken) || checkForWin(humanToken) || isFull();
}