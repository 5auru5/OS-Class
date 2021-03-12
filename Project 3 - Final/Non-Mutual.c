#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 2

void *PrintA(void *threadid)  //prints A value
{
    for (int j = 0; j < 10; j++)
    { //Needs sleep for program to show that mutual exclusion does not work
        for (int i = 0; i < 5; i++)
        {
            sleep(1);
            printf("%i %s", j + 1, ": AAAAAAAAAA");
            printf("\n");
        }
    }
        pthread_exit(NULL);
}
void *PrintB(void *threadid)
{
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            sleep(1);
            printf("%i %s", j + 1, ": BBBBBBBBBB");
            printf("\n");
        }
    }
        pthread_exit(NULL);
    }
int main()
{
    pthread_t threads[NUM_THREADS];
    int rc;
    int i;


        rc = pthread_create(&threads[0], NULL, PrintA, (void *)i);
        if (rc)  //runs thread 0
        {
            printf("Error:unable to create thread, %d\n", rc);
            exit(-1);
        }
        rc = pthread_create(&threads[1], NULL, PrintB, (void *)i);
        if (rc)  //runs thread 1
            {
                printf("Error:unable to create thread, %d\n", rc);
                exit(-1);
            }
    pthread_exit(NULL);
}