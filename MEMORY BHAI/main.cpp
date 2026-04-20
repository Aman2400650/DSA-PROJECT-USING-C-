#include <iostream>
#include "game.h"
using namespace std;

int main() {
    Game g;
    int moves = 0;

    initGame(&g);

    while(true) {
        printBoard(&g);

        if(isFinished(&g)) break;

        playTurn(&g, moves);
    }

    cout << "\nGame Over 🎉\n";
    cout << "Total moves: " << moves << endl;

    return 0;
}