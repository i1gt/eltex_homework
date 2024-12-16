#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
void playerlost(int *sh_time, int sh_time_id);

int main (int argc, char *argv[])
{
    int *sh_time;
    int sh_time_id;
    char* path = "task3test.c";
    key_t key;
    time_t start_time, end_time;

    if (strcmp(argv[0],"blackactive") != 0)
    {
        printf("Use launcher");
        exit (EXIT_FAILURE);
    }

    key = ftok(path, 0);
    if (key == -1) 
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

   if ((sh_time_id = shmget(key, sizeof(long int), 0666|IPC_CREAT|IPC_EXCL)) < 0) 
    {
        if(errno != EEXIST){
            perror("shget failed");
            exit(EXIT_FAILURE);
        } 

        else 
        {
            if((sh_time_id = shmget(key, sizeof(long int), 0)) < 0)
            {
                perror ("shmget failed to find");
                exit(EXIT_FAILURE);
            }
        }
    }

    if ((sh_time = (int *)shmat(sh_time_id, NULL, 0)) == (int *)(-1))
    {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }


    time(&start_time);
    printf("\nBlack player turn\n"
    "Press Enter to continue...\n");
    getchar();
    time(&end_time);
    double ELP_time = difftime(end_time,start_time);
    printf("Turn time: %.2f\n", ELP_time);
    sh_time[1] = ELP_time + sh_time[1];
    printf ("Total time: %d\n" ,sh_time[1]);

    if (sh_time[1] > 9)
    {
        shmdt(sh_time);
        if (shmctl(sh_time_id, IPC_RMID, NULL) == -1) 
        {
            perror("shmctl(IPC_RMID) failed");
            exit(EXIT_FAILURE);
        }   
        execl("task3test", "done", "Black", NULL);   
    }
    
    if (ELP_time > 4)
    {
        shmdt(sh_time);
        if (shmctl(sh_time_id, IPC_RMID, NULL) == -1) 
        {
            perror("shmctl(IPC_RMID) failed");
            exit(EXIT_FAILURE);
        }   
        execl("task3test", "done", "Black", NULL);
    }

    execl("white","whiteactive", NULL);

    shmdt(sh_time);

    if (shmctl(sh_time_id, IPC_RMID, NULL) == -1) 
    {
        perror("shmctl(IPC_RMID) failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void playerlost(int *sh_time, int sh_time_id)
{
    shmdt(sh_time);
    if (shmctl(sh_time_id, IPC_RMID, NULL) == -1)
    {
        perror("shmctl(IPC_RMID) failed");
        exit(EXIT_FAILURE);
    }
    execl("task3test", "done", "Black", NULL);
}