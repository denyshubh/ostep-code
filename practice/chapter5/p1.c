#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for fork()
#include <sys/wait.h> // for wait()

int
main (int args, char *argv[]) {

    printf("I am the first print stmt that should run in main threada (pid:%d)\n", (int) getpid());
    // create a chid process
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        // child process
        printf("I am the child process (pid:%d)\n", (int) getpid());
    } else {
        // parent process
        int wc = wait(NULL); // wait for child process to finish and return the child's pid
        printf("wait() return %d\n", wc);
        printf("I am the parent process (pid:%d)\n", (int) getpid());
    }
    return 0;
}