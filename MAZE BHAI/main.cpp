#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include "maze.h"
using namespace std;

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;

    srand(time(0));

    Maze m;
    initMaze(&m,n);

    chooseRandomEntryExit(&m);

    generateMaze(&m);

    cout << "\nGenerated Maze:\n";
    printMaze(&m);

    this_thread::sleep_for(chrono::seconds(2));
    system("cls");

    cout << "\nSolving...\n";

    if(solveMazeBFS(&m)){
        cout << "\nSolved Path:\n";
        printMaze(&m);
    } else {
        cout << "No path found\n";
    }

    return 0;
}