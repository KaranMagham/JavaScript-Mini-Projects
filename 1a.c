#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_SIZE 10
#define SHM_KEY 0x1234
#define SEM_KEY 0x5678

// Semaphore indices
#define MUTEX 0
#define EMPTY 1
#define FULL 2
// Structure for shared buffer
typedef struct
{
    int buffer[BUFFER_SIZE];
    int in;
    int out;
} SharedBuffer;
// Union required for semctl()
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
// Semaphore wait (P)
void sem_wait_op(int semid, int semnum)
{
    struct sembuf op;
    op.sem_num = semnum;
    op.sem_op = -1;
    op.sem_flg = 0;
    semop(semid, &op, 01);
}
// Semaphore signal (V)
void sem_signal_op(int semid, int semnum)
{
    struct sembuf op;
    op.sem_num = semnum;
    op.sem_op = 1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}
int main()
{
    int shmid, semid;
    SharedBuffer *shm;
    // Create shared memory
    shmid = shmget(SHM_KEY, sizeof(SharedBuffer), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget failed");
        exit(1);
    }
    // Attach shared memory
    shm = (SharedBuffer *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1)
    {
        perror("shmat failed");
        exit(1);
    }
    // Initialize buffer pointers
    shm->in = 0;
    shm->out = 0;
    // Create semaphores
    semid = semget(SEM_KEY, 3, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget failed");
        exit(1);
    }
    // Initialize semaphores
    union semun arg;
    arg.val = 1;
    semctl(semid, MUTEX, SETVAL, arg); // mutex = 1
    arg.val = BUFFER_SIZE;
    semctl(semid, EMPTY, SETVAL, arg); // empty = BUFFER_SIZE
    arg.val = 0;
    semctl(semid, FULL, SETVAL, arg); // full = 0
    // Fork process
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Consumer Process
        int i;
        for (i = 0; i < 10; i++)
        {
            sem_wait_op(semid, FULL);
            sem_wait_op(semid, MUTEX);
            int item = shm->buffer[shm->out];
            printf("Consumer consumed: %d\n", item);
            shm->out = (shm->out + 1) % BUFFER_SIZE;
            sem_signal_op(semid, MUTEX);
            sem_signal_op(semid, EMPTY);
            sleep(1);
        }
        shmdt((void *)shm);
    }
    else
    {
        // Producer Process
        int i;
        for (i = 0; i < 10; i++)
        {
            int item = i + 1;
            sem_wait_op(semid, EMPTY);
            sem_wait_op(semid, MUTEX);
            shm->buffer[shm->in] = item;
            printf("Producer produced: %d\n", item);
            shm->in = (shm->in + 1) % BUFFER_SIZE;
            sem_signal_op(semid, MUTEX);
            sem_signal_op(semid, FULL);
            sleep(1);
        }
        wait(NULL); // Wait for child to finish
        // Cleanup
        shmdt((void *)shm);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }
    return 0;
}
