#include <my_header.h>

typedef struct ticket_state
{
    int ticketNum;
    int flag;
    pthread_mutex_t m_lock;
    // pthread_mutex_t cond_lock;
    pthread_cond_t cond;
} ticket_state_t;

void *sellFun(void *arg)
{
    ticket_state_t *pTicketState = (ticket_state_t *)arg;
    struct timeval nowTime;
    gettimeofday(&nowTime, NULL);
    srand((unsigned int)nowTime.tv_usec);
    while (1)
    {
        pthread_mutex_lock(&pTicketState->m_lock);

        if (pTicketState->ticketNum <= 0 && pTicketState->flag != 0)
        {
            pthread_mutex_unlock(&pTicketState->m_lock);
            break;
        }

        if (pTicketState->ticketNum <= 5 && pTicketState->flag == 0)
        {
            pthread_cond_signal(&pTicketState->cond);
            pthread_mutex_unlock(&pTicketState->m_lock);
            continue;
        }

        double rand_num = (double)rand() / RAND_MAX;

        if (pTicketState->ticketNum > 0 && rand_num < 0.5)
        {
            pTicketState->ticketNum--;
            printf("ticketNum = %d\n", pTicketState->ticketNum);
        }

        pthread_mutex_unlock(&pTicketState->m_lock);
    }
    return NULL;
}

void *purchaseFun(void *arg)
{

    ticket_state_t *pTicketState = (ticket_state_t *)arg;

    pthread_mutex_lock(&pTicketState->m_lock);

    if (pTicketState->ticketNum > 5)
    {
        printf("wait to add\n");
        pthread_cond_wait(&pTicketState->cond, &pTicketState->m_lock);
        pTicketState->ticketNum = pTicketState->ticketNum + 10;
        pTicketState->flag = 1;
    }
    else
    {
        printf("ready to add\n");
        pthread_cond_wait(&pTicketState->cond, &pTicketState->m_lock);
        pTicketState->ticketNum = pTicketState->ticketNum + 10;
        pTicketState->flag = 1;
    }

    pthread_mutex_unlock(&pTicketState->m_lock);
    return NULL;
}

int main(int argc, char *argv[])
{

    ticket_state_t ticketState;
    ticketState.ticketNum = 20;
    ticketState.flag = 0;
    pthread_mutex_init(&ticketState.m_lock, NULL);
    pthread_cond_init(&ticketState.cond, NULL);

    pthread_t pid1, pid2;

    pthread_create(&pid2, NULL, purchaseFun, &ticketState);
    pthread_create(&pid1, NULL, sellFun, &ticketState);

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);

    return 0;
}