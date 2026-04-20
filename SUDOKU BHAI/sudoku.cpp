#include "sudoku.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

bool Sudoku::isSafe(vector<vector<char>>& board,int row,int col,char digit){

    for(int j=0;j<9;j++){
        if(board[row][j]==digit) return false;
    }

    for(int i=0;i<9;i++){
        if(board[i][col]==digit) return false;
    }

    int sr=(row/3)*3;
    int sc=(col/3)*3;

    for(int i=sr;i<sr+3;i++){
        for(int j=sc;j<sc+3;j++){
            if(board[i][j]==digit) return false;
        }
    }
    return true;
}

bool Sudoku::solve(vector<vector<char>>& board,int row,int col){

    if(row==9) return true;

    int nr=row, nc=col+1;
    if(nc==9){
        nr=row+1;
        nc=0;
    }

    if(board[row][col] != '.'){
        return solve(board,nr,nc);
    }

    for(char d='1'; d<='9'; d++){
        if(isSafe(board,row,col,d)){
            board[row][col]=d;

            if(solve(board,nr,nc)) return true;

            board[row][col]='.';
        }
    }
    return false;
}

// 🔥 Generate random sudoku (basic)
void Sudoku::generateBoard(vector<vector<char>>& board){

    srand(time(0));

    // empty board
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            board[i][j]='.';
        }
    }

    // fill diagonal 3x3 boxes randomly
    for(int k=0;k<9;k+=3){
        vector<char> nums = {'1','2','3','4','5','6','7','8','9'};

        for(int i=0;i<9;i++){
            int r = rand()%9;
            swap(nums[i], nums[r]);
        }

        int idx=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                board[k+i][k+j]=nums[idx++];
            }
        }
    }

    // solve full board
    solve(board,0,0);

    // remove some cells for puzzle
    int remove = 40; // difficulty
    while(remove--){
        int r = rand()%9;
        int c = rand()%9;
        board[r][c]='.';
    }
}

void Sudoku::printBoard(vector<vector<char>>& board){

    cout << "\n    ";
    for(int i=0;i<9;i++) cout << i << " ";
    cout << "\n";

    for(int i=0;i<9;i++){

        if(i%3==0 && i!=0)
            cout << "   ------+-------+------\n";

        cout << i << " | ";

        for(int j=0;j<9;j++){

            if(j%3==0 && j!=0) cout << "| ";

            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}