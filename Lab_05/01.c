#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>

#define BUFFER_SIZE 5
#define SHM_NAME "/pc_shm"

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t mutex;
    sem_t empty_count;
    sem_t full_count;
} shared_data;

int main() {

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(shared_data));

    shared_data *data = mmap(0, sizeof(shared_data),
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED, shm_fd, 0);

    // Initialize
    data->in = 0;
    data->out = 0;

    sem_init(&data->mutex, 1, 1);
    sem_init(&data->empty_count, 1, BUFFER_SIZE);
    sem_init(&data->full_count, 1, 0);

    pid_t pid = fork();

    if (pid == 0) {
        // Consumer
        for (int i = 0; i < 10; i++) {

            sem_wait(&data->full_count);
            sem_wait(&data->mutex);

            int item = data->buffer[data->out];
            printf("Consumer consumed: %d\n", item);
            data->out = (data->out + 1) % BUFFER_SIZE;

            sem_post(&data->mutex);
            sem_post(&data->empty_count);

            sleep(1);
        }
    }
    else {
        // Producer
        for (int i = 1; i <= 10; i++) {

            sem_wait(&data->empty_count);
            sem_wait(&data->mutex);

            data->buffer[data->in] = i;
            printf("Producer produced: %d\n", i);
            data->in = (data->in + 1) % BUFFER_SIZE;

            sem_post(&data->mutex);
            sem_post(&data->full_count);

            sleep(1);
        }

        wait(NULL);

        // Cleanup
        sem_destroy(&data->mutex);
        sem_destroy(&data->empty_count);
        sem_destroy(&data->full_count);
        shm_unlink(SHM_NAME);
    }

    return 0;
}
