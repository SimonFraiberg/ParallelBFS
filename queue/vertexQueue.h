#ifndef VERTEX_QUEUE_H
#define VERTEX_QUEUE_H

#include "../SyncGraph/graph.h"

typedef struct
{
    node *head;
    node *tail;
    int size;
    pthread_mutex_t mutex;
} Queue;

Queue *init_Queue();
void insert_Queue(Queue *queue, vertex v);
vertex remove_Queue(Queue *queue);
void destroy_Queue(Queue *queue);
int isQueueEmpty(Queue *queue);
#endif