#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("Type exit to terminate programm\n");
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
        ++i;
    }
    
    char msg[BUFSIZ] = {0};
    printf("PID = %d\n",getpid());
    sleep(1);
    scanf("%s", msg);

    if (strcmp(msg, "exit") == 0)
    {
        printf("EXITING\n");
        exit(EXIT_SUCCESS);
    } else {
        execl(argv[0], argv[0], msg, NULL);
    }
    return 0;
}