#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define MAX 100000

typedef struct {
    int start;
    int end;
} thread_data;


int isPrime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void* find_primes(void* arg) {
    thread_data* data = (thread_data*)arg;

    for (int i = data->start; i <= data->end; i++) {
        if (isPrime(i)) {
            printf("%d\n", i);
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_threads>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    pthread_t threads[N];
    thread_data data[N];

    int segment_size = MAX / N;
    int start = 1;

    for (int i = 0; i < N; i++) {
        data[i].start = start;
        data[i].end = (i == N - 1) ? MAX : start + segment_size - 1;
        start = data[i].end + 1;

        pthread_create(&threads[i], NULL, find_primes, &data[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
