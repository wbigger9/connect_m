#include "connectM.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Starting ConnectM game..." << endl;
    ConnectM game(7, 3);
    game.play();
    cout << "Game over. Press Enter to exit." << endl;
    cin.ignore();
    cin.get();
    return 0;
}
