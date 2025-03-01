#include "connectM.h"
#include <iostream>
#include <cstdlib>  // For atoi()
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {  // Check if the correct number of arguments is provided
        cout << "Usage: ./connectM <N> <M> <H>\n";
        cout << "  N = Board size (3 to 10)\n";
        cout << "  M = Disks required to win (2 to N)\n";
        cout << "  H = First player (1 = Human, 0 = Computer)\n";
        return 1;  // Exit with error
    }

    int boardSize = atoi(argv[1]);  // Convert arguments to integers
    int M = atoi(argv[2]);
    int humanFirst = atoi(argv[3]);

    // Validate inputs
    if (boardSize < 3 || boardSize > 10 || M < 2 || M > boardSize || (humanFirst != 0 && humanFirst != 1)) {
        cout << "Invalid arguments! Please follow the correct format.\n";
        return 1;
    }

    // Create and start the game
    ConnectM game(boardSize, M, humanFirst);
    game.play();
    return 0;
}
