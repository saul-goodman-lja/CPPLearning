#include "queue.h"

int offer(Queue *queue, int net_fd)
{
    Node *newNode = calloc(1, sizeof(Node));

    newNode->net_fd = net_fd;

    if(queue->size == 0)
    {
        queue->head = newNode;
        queue->tail = newNode;
    }
    else
    {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    queue->size++;

    return 0;
}

int poll(Queue *queue)
{
    Node *temp = queue->head;
    if(temp == NULL){
        perror("队列为空，不可出队！");
        exit(1);
    }

    queue->head = temp->next;
    queue->size--;
    if(queue->size == 0){
        queue->tail = NULL;
    }

    free(temp);
    return 0;
}