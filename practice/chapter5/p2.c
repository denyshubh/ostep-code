#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for fork()
#include <sys/wait.h> // for wait()
#include <string.h> // for strdup()

int
main (int args, char *argv[]) {
    
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        printf("I am the child process (pid:%d)\n", (int) getpid());
        // let's run the wc command using execvp
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: wc (word count)
        myargs[1] = strdup("p2.c"); // argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // runs word count
        printf("this shouldn't print out");

    } else {
        wait(NULL);
        printf("I am the parent process (pid:%d)\n", (int) getpid());
    }
    
    
    return 0;    
}