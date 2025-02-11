#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <string.h>
#define PATH "task4server.c"

struct msg_buffer
{
    long msg_type;
    char msg_text[100];
} message;

void makemove(char *move)
{
    strcpy(message.msg_text, move);
}
void block(int semid)
{
    struct sembuf sb = {0, -1, 0};
    semop(semid, &sb, 1);
}
void unblock(int semid)
{
    struct sembuf sb = {0, 1, 0};
    semop(semid, &sb, 1);
}

int main()
{
    char *movelist[] = {
        "pawn e5\n",
        "knight c6\n",
        "pawn d4\n",
        "bishop 5c\n",
        "queen 6f\n",
        "queen f2\n",
        NULL};

    key_t key;
    key_t semkey;
    int msgid = 0;
    int semid = 0;
    int turn = 0;
    key = ftok(PATH, 0);
    semkey = ftok(PATH, 1);

    msgid = msgget(key, 0666 | IPC_CREAT);
    semid = semget(semkey, 1, 0666 | IPC_CREAT);
    semctl(semid, 0, SETVAL, 0);
    message.msg_type = 1;

    unblock(semid);
    while (movelist[turn] != NULL)
    {
        msgrcv(msgid, &message, sizeof(message), 0, 0);
        printf("White makes move: %s", message.msg_text);

        sleep(1);

        makemove(movelist[turn]);
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("Black makes move: %s", message.msg_text);
        turn++;
    }
    printf("Checkmate, white lost");
    msgctl(msgid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
