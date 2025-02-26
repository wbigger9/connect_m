#include "connectM.h"
#include <iostream>
using namespace std;

int main() {
    ConnectM game(11, 3);  // Create a 7x7 ConnectM game with M=4
    game.play();          // Start game loop
    return 0;
}
