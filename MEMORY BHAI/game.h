#ifndef GAME_H
#define GAME_H

const int SIZE = 4;

struct Game {
    char board[SIZE][SIZE];
    bool revealed[SIZE][SIZE];
};

void initGame(Game* g);
void shuffleBoard(Game* g);
void printBoard(Game* g);
bool isFinished(Game* g);
void playTurn(Game* g, int& moves);

#endif