#include "vertexQueue.h"

Queue *init_Queue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    pthread_mutex_init(&(queue->mutex), NULL);
    return queue;
}

void insert_Queue(Queue *queue, vertex v)
{

    pthread_mutex_lock(&(queue->mutex));

    node *node = createNode(v);

    if (queue->head == NULL)
    {
        queue->head = node;
        queue->tail = node;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->size++;
    pthread_mutex_unlock(&(queue->mutex));
}

vertex remove_Queue(Queue *queue)
{

    pthread_mutex_lock(&(queue->mutex));
    node *node = queue->head;
    if (queue->head == NULL)
    {
        perror("queue is empty cant pop");
    }
    else
    {
        node = queue->head;
        queue->head = queue->head->next;
    }
    queue->size--;
    vertex v = node->v;
    free(node);
    pthread_mutex_unlock(&(queue->mutex));
    return v;
}

int isQueueEmpty(Queue *queue)
{
    return (queue->head == NULL);
}

void destroy_Queue(Queue *queue)
{
    node *temp;

    while (queue->head != NULL)
    {
        temp = queue->head;
        queue->head = queue->head->next;

        free(temp);
    }
    pthread_mutex_destroy(&queue->mutex);
    free(queue);
}
