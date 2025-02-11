#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int i) {
    printf("recived SIGINT\n");
}

void* thread_sigint(void * arg)
{
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigaction(SIGINT, &sa, NULL);

    while (1) sleep(1);
    return NULL;
}

void* thread_quit(void * arg)
{
    sigset_t newset2;
    sigemptyset(&newset2);
    sigaddset(&newset2, SIGQUIT);
    if (pthread_sigmask(SIG_BLOCK, &newset2, NULL) != 0) 
        {
        perror("SIGQUIT failed");
        return NULL;
        }

    int sigrcv;
    while (1)
    {
        if (sigwait(&newset2, &sigrcv) == 0)
        {
            printf("Recived signal = %d\n", sigrcv);
            exit (EXIT_SUCCESS);
        }
    }
    return NULL;
}

int main() 
{
    printf("My pid %d\n", getpid());

    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGQUIT);
    pthread_sigmask(SIG_BLOCK, &newset, NULL);

    printf("blocking signals\n");
    
    pthread_t threads[1];
    pthread_create(&threads[0], NULL, thread_sigint, NULL);
    pthread_create(&threads[1], NULL, thread_quit, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

