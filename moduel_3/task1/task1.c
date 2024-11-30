#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#define BUFSIZE 4096

void abrt_handler()
{
const char *fifo = "fifo";
char buf[BUFSIZE];

printf ("Process terminated making fifo\n");
    if (mkfifo(fifo, 0777) == -1)
    {
        unlink(fifo);
        mkfifo(fifo, 0777);
        printf("fifo recreated\n");

        if (errno != EEXIST)
        {
            printf ("Failed to create fifo\n");
            exit (EXIT_FAILURE);
        }
    };

char msg[] = "process was terminated by signal";
int fd = open(fifo, O_RDWR);
int fdw = write (fd, &msg, strlen(msg));
int fdr = read(fd, &buf, sizeof(buf));
printf("\n%s \n", buf);

if (fd == -1 || fdw == -1 || fdr == -1) 
    {
        printf("Oops something went wrong");
        exit (EXIT_FAILURE);
    } 

exit (EXIT_SUCCESS);
}

int main (int argc, char ** argv)
{
    struct sigaction sa;
    sa.sa_handler = abrt_handler;
    sigaction(SIGABRT, &sa, 0);

    printf("PID = %i\n"
            "Type 1 to SIGABRT the process\n"
            "Type 2 to use any siganl\n"
            "Type 3 to exit\n", getpid());

    int t = 0;
    while (1)
    {
    scanf("%d", &t);
    switch (t)
        {
        case 1: 
            kill (getpid(), SIGABRT);
            break;

        case 2:
            int z;
            printf("Choose signal\n");
            scanf("%d", &z);
            kill (getpid(), z);
            break;

        case 3:
            exit (EXIT_SUCCESS);

        default:
            printf("Invalid option");
        }
    }
    return EXIT_FAILURE;
}