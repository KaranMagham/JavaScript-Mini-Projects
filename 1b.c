#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MSG_KEY 0x1234
#define MSG_SIZE sizeof(struct message) - sizeof(long)
#define NUM_ITEMS 10
// Message structure
struct message
{
    long msg_type;
    int data;
};
int main()
{
    int msgid;
    pid_t pid;
    // Create message queue
    msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msgid < 0)
    {
        perror("msgget failed");
        exit(1);
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0)
    {
        // Consumer process
        struct message msg;
        for (int i = 0; i < NUM_ITEMS; i++)
        {
            if (msgrcv(msgid, &msg, MSG_SIZE, 1, 0) < 0)
            {
                perror("msgrcv failed");
                exit(1);
            }
            printf("Consumer received: %d\n", msg.data);
            sleep(1);
        }
    }
    else
    {
        // Producer process
        struct message msg;
        for (int i = 0; i < NUM_ITEMS; i++)
        {
            msg.msg_type = 1;
            msg.data = i + 1;
            if (msgsnd(msgid, &msg, MSG_SIZE, 0) < 0)
            {
                perror("msgsnd failed");
                exit(1);
            }
            printf("Producer sent: %d\n", msg.data);
            sleep(1);
        }
        wait(NULL); // Wait for consumer
        // Cleanup message queue
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}