#ifndef QUEUE_H
#define QUEUE_H

#include "maze.h"

struct Queue {
    Position data[MAX_SIZE * MAX_SIZE];
    int front, rear, size;
};

void initQueue(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, Position p);
Position dequeue(Queue* q);

#endif