#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    int *sh_time = NULL;
    key_t key = 0;
    int sh_time_id = 0;
    char *path = "task3test.c";

    if (strcmp(argv[0], "done") == 0) 
    {
        printf("%s has lost!\n", argv[1]);     
        exit(EXIT_SUCCESS);
    }

    key = ftok(path, 0);
    if (key == -1) 
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }


    if ((sh_time_id = shmget(key, sizeof(long int), 0666|IPC_CREAT|IPC_EXCL)) < 0) 
    {
        if (errno != EEXIST)
        {
            perror("shmget failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            sh_time_id = shmget(key, sizeof(BUFSIZ), 0);
            if (sh_time_id < 0)
            {
                perror("shmget failed to find");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (execl("white", "whiteactive" , NULL) < 0) 
    {
        perror("execl failed");
        exit(EXIT_FAILURE);
    }

    shmdt(sh_time);
    if (shmctl(sh_time_id, IPC_RMID, NULL) == -1)
    {
        perror("shmctl(IPC_RMID) failed");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}