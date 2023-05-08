#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int
main (int args, char *argv[]) {
    
    int x = 10; // uses 4 bytes of stack memory
    int rc = fork();    // creating a child process
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {   // child process
        printf("I am the child process (pid:%d)\n", (int) getpid());
        x = 20; // changing the value of x in the child process
        printf("value of x is %d and address of x in (%p)\n", x, &x);
    } else {    // parent process
        wait(NULL);    // wait for child process to finish and return the child's pid
        printf("I am the parent process (pid:%d)\n", (int) getpid());
        printf("x is %d and address of x in (%p)\n", x, &x);
    }

    
    return 0;
}