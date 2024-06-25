#include <my_header.h>

typedef struct node_t{
    int net_fd;
    struct node_t *next;
} Node;

typedef struct queue_t{
    Node *head;
    Node *tail;
    int size;
} Queue;

int offer(Queue *queue, int net_fd);

int poll(Queue *queue);