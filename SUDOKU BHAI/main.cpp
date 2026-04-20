#include <iostream>
#include "sudoku.h"
using namespace std;

int main(){

    vector<vector<char>> board(9, vector<char>(9,'.'));

    Sudoku s;

    s.generateBoard(board);

    cout << "Generated Sudoku:\n";
    s.printBoard(board);

    cout << "\nSolving...\n";

    s.solve(board,0,0);

    cout << "\nSolved Sudoku:\n";
    s.printBoard(board);

    return 0;
}