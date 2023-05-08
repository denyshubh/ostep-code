#include <stdio.h>
#include <stdlib.h>
#include "common_threads.h"
#include <pthread.h>

volatile int counter = 0; // volatile: prevent compiler from optimizing and force it to read from memory every time.

int loops;

// creating worker of type void* and taking void* as argument because void* can be anything/any type
void *worker(void *arg) {
    int i;
    acquire(); // acquire lock
    for (i = 0; i < loops; i++) {
        counter++;
    }
    release(); // release lock
    return NULL;
}


int
main(int args, char *argv[]) {
    if (args != 2) {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2; // create two threads of type pthread_t

    printf("Initial value: %d\n", counter);

    Pthread_create(&p1, NULL, worker, NULL); // create thread p1
    Pthread_create(&p2, NULL, worker, NULL); // create thread p2

    Pthread_join(p1, NULL); // wait for thread p1 to finish
    Pthread_join(p2, NULL); // wait for thread p2 to finish

    printf("Final value: %d\n", counter);
    return 0;
}

