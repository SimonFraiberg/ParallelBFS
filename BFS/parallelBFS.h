#ifndef PARALLEL_BFS_H
#define PARALLEL_BFS_H

#include "../queue/vertexQueue.h"
#include "../ThreadPool/ThreadPool.h"
#include "../ThreadPool/TaskQueue.h"
#include "../SyncGraph/graph.h"
struct bfsArgs
{
    Graph *graph;
    Queue *Fcurrent;
    Queue *Fnext;
    vertex v;
    int *distances;
    ThreadPool *q;
};

typedef struct bfsArgs bfsArgs;

void bfs(Graph *graph, int **m);
void parallel_bfs(Graph *graph, vertex source, int *mLine);
void *parallel_bfs_visit(void *args);

#endif
