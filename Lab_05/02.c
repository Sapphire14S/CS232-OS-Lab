#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// #include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
// #include <sys/wait.h>

#define SHM_NAME "/rw_shm"
/// @brief 
typedef struct {
    int readcount;
    int writecount;
    int data;

    sem_t mutex;
    sem_t wrt;
    sem_t readTry;
    sem_t resource;

} shared_data;

void reader(shared_data *sh, int id) {

    // ENTRY SECTION
    sem_wait(&sh->readTry);
    sem_wait(&sh->mutex);

    sh->readcount++;
    if (sh->readcount == 1)
        sem_wait(&sh->resource);

    sem_post(&sh->mutex);
    sem_post(&sh->readTry);

    // CRITICAL SECTION
    printf("Reader %d reading data: %d\n", id, sh->data);
    sleep(1);

    // EXIT SECTION
    sem_wait(&sh->mutex);

    sh->readcount--;
    if (sh->readcount == 0)
        sem_post(&sh->resource);

    sem_post(&sh->mutex);
}

void writer(shared_data *sh, int id) {

    // ENTRY SECTION
    sem_wait(&sh->wrt);
    sh->writecount++;
    if (sh->writecount == 1)
        sem_wait(&sh->readTry);
    sem_post(&sh->wrt);

    sem_wait(&sh->resource);

    // CRITICAL SECTION
    sh->data += 10;
    printf("Writer %d writing data: %d\n", id, sh->data);
    sleep(2);

    // EXIT SECTION
    sem_post(&sh->resource);

    sem_wait(&sh->wrt);
    sh->writecount--;
    if (sh->writecount == 0)
        sem_post(&sh->readTry);
    sem_post(&sh->wrt);
}

int main() {

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(shared_data));

    shared_data *sh = mmap(NULL, sizeof(shared_data),
                           PROT_READ | PROT_WRITE,
                           MAP_SHARED, shm_fd, 0);

    // Initialize
    sh->readcount = 0;
    sh->writecount = 0;
    sh->data = 0;

    sem_init(&sh->mutex, 1, 1);
    sem_init(&sh->wrt, 1, 1);
    sem_init(&sh->readTry, 1, 1);
    sem_init(&sh->resource, 1, 1);

    // Create processes
    for (int i = 1; i <= 2; i++) {
        if (fork() == 0) {
            reader(sh, i);
            exit(0);
        }
    }

    for (int i = 1; i <= 2; i++) {
        if (fork() == 0) {
            writer(sh, i);
            exit(0);
        }
    }

    for (int i = 0; i < 4; i++)
        wait(NULL);

    // Cleanup
    sem_destroy(&sh->mutex);
    sem_destroy(&sh->wrt);
    sem_destroy(&sh->readTry);
    sem_destroy(&sh->resource);

    shm_unlink(SHM_NAME);

    return 0;
}
