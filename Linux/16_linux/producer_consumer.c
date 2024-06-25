#include <my_header.h>

typedef struct node {
    int val;
    struct node *next;
} Node;

typedef struct obs_queue {
    Node *head;
    Node *tail;
    int size;
} queue_obs;

typedef struct t_state {
    queue_obs *objects;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} thread_state;

void print_val(queue_obs *queue) {
    if (queue->head == NULL) {
        return;
    }

    Node *cur = queue->head;
    printf("== ");
    while (cur) {
        printf("%3d ", cur->val);
        cur = cur->next;
    }
    printf("== \n");
}

void push_queue(queue_obs *queue, int val) {

    Node *new_node = (Node *)calloc(1, sizeof(Node));
    new_node->val = val;

    if (queue->size == 0) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }

    queue->size++;
}

int pop_queue(queue_obs *queue) {

    if (queue == NULL || queue->size == 0) {
        return 0;
    }

    Node *cur = queue->head;

    int val = cur->val;
    queue->head = cur->next;
    queue->size--;

    if (queue->size == 0) {
        queue->tail = NULL;
    }

    free(cur);

    return val;
}

void *producer(void *arg) {

    thread_state *threadState = (thread_state *)arg;

    while (1) {

        pthread_mutex_lock(&threadState->lock);

        while (threadState->objects->size == 20) {
            // if (threadState->objects->size == 20) {
                pthread_cond_wait(&threadState->cond, &threadState->lock);
            // }
            // if(threadState->objects->size < 20){
            //     break;
            // }
        }
        int cur_size = threadState->objects->size;
        int val = rand() % 1000;
        push_queue(threadState->objects, val);
        print_val(threadState->objects);

        if (cur_size == 0) {
            pthread_cond_signal(&threadState->cond);
        }

        pthread_mutex_unlock(&threadState->lock);

        sleep(1);
    }

    return NULL;
}

void *consumer(void *arg) {

    thread_state *threadState = (thread_state *)arg;
    sleep(5);

    while (1) {

        pthread_mutex_lock(&threadState->lock);
        while (threadState->objects->size == 0) {
            // if (threadState->objects->size == 0) {
                pthread_cond_wait(&threadState->cond, &threadState->lock);
            // }
            // if (threadState->objects->size > 0) {
            //     break;
            // }
        }
        int cur_size = threadState->objects->size;
        int val = pop_queue(threadState->objects);
        printf("consume %d\n", val);
        print_val(threadState->objects);

        if (cur_size == 20) {
            pthread_cond_signal(&threadState->cond);
        }

        pthread_mutex_unlock(&threadState->lock);

        sleep(1);
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    thread_state threadState;
    memset(&threadState, 0, sizeof(threadState));
    threadState.objects = calloc(1, sizeof(queue_obs));

    for (int i = 0; i < 10; i++) {
        int val = rand() % 1000;
        push_queue(threadState.objects, val);
    }
    print_val(threadState.objects);
    pthread_mutex_init(&threadState.lock, NULL);
    pthread_cond_init(&threadState.cond, NULL);

    pthread_t pid1, pid2, cid1, cid2, cid3;

    int ret1 = pthread_create(&pid1, NULL, producer, &threadState);
    THREAD_ERROR_CHECK(ret1, "pthread_create");

    int ret2 = pthread_create(&pid2, NULL, producer, &threadState);
    THREAD_ERROR_CHECK(ret2, "pthread_create");

    int ret3 = pthread_create(&cid1, NULL, consumer, &threadState);
    THREAD_ERROR_CHECK(ret3, "pthread_create");

    int ret4 = pthread_create(&cid2, NULL, consumer, &threadState);
    THREAD_ERROR_CHECK(ret4, "pthread_create");

    int ret5 = pthread_create(&cid3, NULL, consumer, &threadState);
    THREAD_ERROR_CHECK(ret5, "pthread_create");

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    pthread_join(cid1, NULL);
    pthread_join(cid2, NULL);
    pthread_join(cid3, NULL);

    return 0;
}