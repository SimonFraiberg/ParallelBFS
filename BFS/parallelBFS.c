
#include <semaphore.h>
#include "parallelBFS.h"

void *parallel_bfs_visit(void *args)
{
    /* Extract arguments */
    bfsArgs *data = (bfsArgs *)args;
    Graph *graph = data->graph;
    Queue *Fcurrent = data->Fcurrent;
    Queue *Fnext = data->Fnext;
    vertex v = data->v;
    int *distances = data->distances;
    ThreadPool *q = data->q;

    free(data);

    node *neighborsPtr = graph->adjacencyLists[v];

    while (neighborsPtr != NULL)
    {
        vertex neighbor = neighborsPtr->v;

        /* Synchronously increment the number of visits for the neighbor */
        pthread_mutex_lock(&graph->num_visits_mutexes[neighbor]);
        int neighborVisits = graph->numVisits[neighbor]++;
        pthread_mutex_unlock(&graph->num_visits_mutexes[neighbor]);

        /* If the neighbor has not been visited, add a new task to the queue */
        if (neighborVisits == 0)
        {
            insert_Queue(Fnext, neighbor);
            distances[neighbor] = distances[v] + 1;
        }

        neighborsPtr = neighborsPtr->next;
    }

    /* Decrement the number of running threads */
    --(q->runningThreads);
}

void parallel_bfs(Graph *graph, vertex source, int *mLine)
{

    graph->numVisits[source]++;
    mLine[source] = 0;
    Queue *Fcurrent = init_Queue();
    Queue *Fnext;
    Queue *temp;

    bfsArgs *args;

    TaskQueue q;
    initQueue(&q);

    ThreadPool pool;
    pool.maxThreads = 4;
    pool.runningThreads = 0;
    pool.q = &q;

    insert_Queue(Fcurrent, source);

    while (!isQueueEmpty(Fcurrent))
    {
        Fnext = init_Queue();
        while (!isQueueEmpty(Fcurrent))
        {
            vertex v = remove_Queue(Fcurrent);
            args = malloc(sizeof(bfsArgs));
            args->graph = graph;
            args->Fcurrent = Fcurrent;
            args->Fnext = Fnext;
            args->distances = mLine;
            args->q = &pool;
            args->v = v;

            TaskData td = {parallel_bfs_visit, args};
            insert(pool.q, td);
        }

        runThreadPool(&pool);
        temp = Fcurrent;
        Fcurrent = Fnext;
        destroy_Queue(temp);
    }
    destroy_Queue(Fcurrent);
}

void bfs(Graph *graph, int **m)
{
    int numVertices = graph->numVertices;

    for (vertex v = 0; v < numVertices; v++)
    {

        for (vertex j = 0; j < numVertices; j++)
        {
            m[v][j] = -1;
            graph->numVisits[j] = 0;
        }

        parallel_bfs(graph, v, m[v]);
    }
}