#include "queue.h"
#include <iostream>
using namespace std;

void initQueue(Queue* q) {
    q->front = q->rear = q->size = 0;
}

bool isEmpty(Queue* q) {
    return q->size == 0;
}

void enqueue(Queue* q, Position p) {
    q->data[q->rear++] = p;
    q->size++;
}

Position dequeue(Queue* q) {
    q->size--;
    return q->data[q->front++];
}