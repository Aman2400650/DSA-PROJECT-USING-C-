#ifndef MAZE_H
#define MAZE_H

const int MAX_SIZE = 50;

struct Position {
    int x, y;
};

enum { TOP = 0, RIGHT = 1, BOTTOM = 2, LEFT = 3 };

struct Cell {
    int visited;
    int walls[4];
    int inPath;
};

struct Maze {
    int size;
    Cell cells[MAX_SIZE][MAX_SIZE];
    Position entry;
    Position exit;
};

void initMaze(Maze* m, int n);
void chooseRandomEntryExit(Maze* m);
void generateMaze(Maze* m);
void printMaze(const Maze* m);
bool solveMazeBFS(Maze* m);

#endif