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
void termh ()
{
printf ("Process terminated making fifo\n");
const char *fifo = "fifo";
    
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
char buf[BUFSIZE];
int fdr = read(fd, &buf, sizeof(buf));
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
    sa.sa_handler = termh;
    sigaction(SIGTERM, &sa, 0);

    printf("PID = %i\nType 1 to SIGTERM the process\nType 2 to use any siganl\nType 3 to exit\n", getpid());
    for(int t = 0; t!=-1;)
    {
        scanf("%d", &t);
        if (t==1)
            {
            kill (getpid(), 15);
            }
        if (t==2)
            {
                int z;
                printf("Choose signal\n");
                scanf("%d", &z);
                kill (getpid(), z);
            }
        if (t==3)
        {
            return 1;
        }
    }
    return EXIT_FAILURE;
}