#include <my_header.h>

int tk_num = 20;
int flag = 0;

void *add_ticket(void *mutex)
{
    pthread_mutex_t *p = (pthread_mutex_t *)mutex;

    while (1)
    {
        pthread_mutex_lock(p);

        if (tk_num < 5)
        {
            tk_num += 10;
            pthread_mutex_unlock(p);
            flag = 1;
            break;
        }

        pthread_mutex_unlock(p);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);
    int res = pthread_create(&thread, NULL, add_ticket, &mutex);
    THREAD_ERROR_CHECK(res, "pthread_create");

    srand(time(NULL));

    while (1)
    {   
        if(tk_num < 5 && flag == 0){
            continue;
        }
        if (tk_num > 0)
        {
            if ((((double)(rand() % 10))) / 10 < 0.5)
            {   
                pthread_mutex_lock(&mutex);
                tk_num--;
                printf("num = %d\n", tk_num);

                if (tk_num == 0 && flag == 1)
                {
                    break;
                }

                pthread_mutex_unlock(&mutex);
            }
        }
    }

    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
