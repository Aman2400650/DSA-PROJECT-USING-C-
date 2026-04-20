#include <windows.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <vector>
#include <random>

#include "maze.h"
#include "queue.h"

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

bool inBounds(Maze* m, int x, int y) {
    return x >= 0 && x < m->size && y >= 0 && y < m->size;
}

void initMaze(Maze* m, int n) {
    m->size = n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            m->cells[i][j].visited = 0;
            m->cells[i][j].inPath = 0;
            for(int k=0;k<4;k++) m->cells[i][j].walls[k]=1;
        }
    }
}

void chooseRandomEntryExit(Maze* m) {
    m->entry = {0, rand()%m->size};
    m->exit  = {m->size-1, rand()%m->size};

    // open entry/exit walls
    m->cells[m->entry.y][m->entry.x].walls[LEFT] = 0;
    m->cells[m->exit.y][m->exit.x].walls[RIGHT] = 0;
}

void generateMaze(Maze* m) {
    stack<Position> st;

    Position start = m->entry;
    st.push(start);
    m->cells[start.y][start.x].visited = 1;

    random_device rd;
    mt19937 g(rd());

    while(!st.empty()) {
        Position cur = st.top();

        vector<int> dirs = {0,1,2,3};
        shuffle(dirs.begin(), dirs.end(), g);

        bool moved = false;

        for(int d : dirs) {
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];

            if(inBounds(m,nx,ny) && !m->cells[ny][nx].visited) {

                m->cells[cur.y][cur.x].walls[d] = 0;
                m->cells[ny][nx].walls[(d+2)%4] = 0;

                m->cells[ny][nx].visited = 1;

                st.push({nx,ny});
                moved = true;
                break;
            }
        }

        if(!moved) st.pop();
    }
}

void printMaze(const Maze* m) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int n = m->size;

    cout << "\n";

    for(int i=0;i<n;i++) cout << "+---";
    cout << "+\n";

    for(int y=0; y<n; y++) {

        for(int x=0; x<n; x++) {

            if(m->cells[y][x].walls[LEFT]) cout << "|";
            else cout << " ";

            if(x == m->entry.x && y == m->entry.y) {
                SetConsoleTextAttribute(h, 10);
                cout << " S ";
            }
            else if(x == m->exit.x && y == m->exit.y) {
                SetConsoleTextAttribute(h, 12);
                cout << " E ";
            }
            else if(m->cells[y][x].inPath) {
                SetConsoleTextAttribute(h, 14);
                cout << " * ";
            }
            else {
                SetConsoleTextAttribute(h, 7);
                cout << "   ";
            }
        }

        SetConsoleTextAttribute(h, 7);
        cout << "|\n";

        for(int x=0; x<n; x++) {
            cout << "+";
            if(m->cells[y][x].walls[BOTTOM]) cout << "---";
            else cout << "   ";
        }
        cout << "+\n";
    }
}

bool solveMazeBFS(Maze* m) {
    Queue q;
    initQueue(&q);

    int visited[MAX_SIZE][MAX_SIZE] = {0};
    Position parent[MAX_SIZE][MAX_SIZE];

    enqueue(&q, m->entry);
    visited[m->entry.y][m->entry.x] = 1;

    while(!isEmpty(&q)) {

        Position cur = dequeue(&q);

        // animation (just showing traversal, not marking final path)
        printMaze(m);
        this_thread::sleep_for(chrono::milliseconds(40));
        system("cls");

        if(cur.x == m->exit.x && cur.y == m->exit.y) {

            Position p = cur;

            while(!(p.x == m->entry.x && p.y == m->entry.y)) {
                m->cells[p.y][p.x].inPath = 1;

                printMaze(m);
                this_thread::sleep_for(chrono::milliseconds(80));
                system("cls");

                p = parent[p.y][p.x];
            }

            m->cells[m->entry.y][m->entry.x].inPath = 1;
            return true;
        }

        for(int d=0; d<4; d++) {
            if(m->cells[cur.y][cur.x].walls[d] == 0) {
                int nx = cur.x + dx[d];
                int ny = cur.y + dy[d];

                if(inBounds(m,nx,ny) && !visited[ny][nx]) {
                    visited[ny][nx] = 1;
                    parent[ny][nx] = cur;
                    enqueue(&q,{nx,ny});
                }
            }
        }
    }
    return false;
}