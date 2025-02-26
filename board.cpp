#include "board.h"
#include <cmath>

// Constructor
Board::Board(int size, int m) : boardSize(size), M(m), recentCol(-1), recentRow(-1) {
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

    char horizontalPlane[boardSize];
    char verticalPlane[boardSize];
    // 🔹 Extract Horizontal Plane
    for (int i = 0; i < boardSize; i++) {
        horizontalPlane[i] = board[recentRow][i];
    }
    if (countConsecutive(horizontalPlane, boardSize, token, M) >= M) {
        return true;
    }

    // 🔹 Extract Vertical Plane
    for (int i = 0; i < boardSize; i++) {
        verticalPlane[i] = board[i][recentCol];
    }
    if (countConsecutive(verticalPlane, boardSize, token, M) >= M) {
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
int Board::setWeight(int row, int col) {
    // 1️⃣ Calculate distance from the middle column
    int middleCol = boardSize / 2;
    if (boardSize % 2 == 0) {
        middleCol -= 1;  // Adjust for even-sized boards
    }
    int distanceFromMiddle = abs(col - middleCol);

    // 2️⃣ Calculate distance from the bottom
    int distanceFromBottom = (boardSize - 1) - row;

    // 3️⃣ Define weight scaling factors
    double middleScaling = 2.0;  // ✅ Middle column has a stronger effect
    double bottomScaling = 1.5;  // ✅ Favor bottom rows slightly less than center

    // 4️⃣ Compute final weight
    int weight = round(30 - (middleScaling * distanceFromMiddle) - (bottomScaling * distanceFromBottom));

    // 5️⃣ Ensure weight is non-negative
    return max(1, weight);
}
