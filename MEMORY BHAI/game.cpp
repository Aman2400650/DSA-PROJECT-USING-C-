#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void initGame(Game* g) {
    char values[16] = {
        'A','A','B','B','C','C','D','D',
        'E','E','F','F','G','G','H','H'
    };

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            g->revealed[i][j] = false;
        }
    }

    // shuffle
    srand(time(0));
    for(int i=0;i<16;i++){
        int r = rand() % 16;
        char temp = values[i];
        values[i] = values[r];
        values[r] = temp;
    }

    int k = 0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            g->board[i][j] = values[k++];
        }
    }
}

void printBoard(Game* g) {
    cout << "\n    ";
    for(int i=0;i<SIZE;i++) cout << i << "   ";
    cout << "\n";

    for(int i=0;i<SIZE;i++) {
        cout << "  +";
        for(int j=0;j<SIZE;j++) cout << "---+";
        cout << "\n";

        cout << i << " |";
        for(int j=0;j<SIZE;j++) {
            if(g->revealed[i][j])
                cout << " " << g->board[i][j] << " |";
            else
                cout << " * |";
        }
        cout << "\n";
    }

    cout << "  +";
    for(int j=0;j<SIZE;j++) cout << "---+";
    cout << "\n";
}

bool isFinished(Game* g) {
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(!g->revealed[i][j])
                return false;
        }
    }
    return true;
}

void playTurn(Game* g, int& moves) {
    int r1,c1,r2,c2;

    cout << "Enter first position (row col) (-1 to exit): ";
    cin >> r1;

    if(r1 == -1) {
    exit(0);
    }

cin >> c1;

    cout << "Enter second position (row col): ";
    cin >> r2 >> c2;

    if(r1<0 || r1>=SIZE || c1<0 || c1>=SIZE ||
       r2<0 || r2>=SIZE || c2<0 || c2>=SIZE ||
       g->revealed[r1][c1] || g->revealed[r2][c2] ||
       (r1==r2 && c1==c2)){
        cout << "Invalid input\n";
        return;
    }

    g->revealed[r1][c1] = true;
    g->revealed[r2][c2] = true;

    printBoard(g);

    if(g->board[r1][c1] != g->board[r2][c2]){
        cout << "Not match\n";
        g->revealed[r1][c1] = false;
        g->revealed[r2][c2] = false;
    } else {
        cout << "Match\n";
    }

    moves++;
}