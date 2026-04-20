#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
using namespace std;

class Sudoku {
public:
    bool isSafe(vector<vector<char>>& board, int row, int col, char digit);
    bool solve(vector<vector<char>>& board, int row, int col);
    void generateBoard(vector<vector<char>>& board);
    void printBoard(vector<vector<char>>& board);
};

#endif