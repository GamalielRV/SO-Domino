
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

unsigned int sleep(unsigned int seconds);
pthread_mutex_t myMutex1;
pthread_mutex_t myMutex2;
pthread_mutex_t myMutex3;

typedef struct
{
    pthread_mutex_t* next;
    pthread_mutex_t* current;
    int id;

} MutexNode;



void *print_message_function(void *ptr);



main()
{
    pthread_t thread1, thread2, thread3;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    char *message3 = "Thread 3";
    int iret1, iret2, iret3;

    /* Create independent threads each of which will execute function */
    pthread_mutex_init(&myMutex1, NULL);
    pthread_mutex_init(&myMutex2, NULL);
    pthread_mutex_init(&myMutex3, NULL);

    MutexNode node1;
    node1.current = &myMutex1;
    node1.next = &myMutex2;
    node1.id = 1;

    MutexNode node2;
    node2.current = &myMutex2;
    node2.next = &myMutex3;
    node2.id = 2;

    MutexNode node3;
    node3.current = &myMutex3;
    node3.next = &myMutex1;
    node3.id = 3;
    
    pthread_mutex_lock(&myMutex2);
    pthread_mutex_lock(&myMutex3);

    iret1 = pthread_create(&thread1, NULL, print_message_function, &node1);
    iret2 = pthread_create(&thread2, NULL, print_message_function,  &node2);
    iret3 = pthread_create(&thread3, NULL, print_message_function, &node3);

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);
    exit(0);
}

void *print_message_function(void *ptr)
{
    MutexNode *node = (MutexNode *) ptr;
    while (1)
    {
        /* code */
        pthread_mutex_lock(node->current);
        for (int i = 0; i < 4; i++)
        {
            sleep(1);
            printf("Estoy aqui %d\n", node->id);
        }
        pthread_mutex_unlock(node->next);
    }
    

}
