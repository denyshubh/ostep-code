#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for fork()
#include <sys/wait.h> // for wait()
#include <string.h> // for strdup()
#include <fcntl.h> // for open()

int main(int argc, char *argv[]) {

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("I am the child process (pid:%d)\n", (int) getpid());

        // redirect stdout to a file
        close(STDOUT_FILENO); // close the existing file descriptor
        open("./p3.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        printf("Message after STDOUT IS CLODES IN PROCESS (pid:%d)\n", (int) getpid());
        // let's run the wc command using execvp
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: wc (word count)
        myargs[1] = strdup("p2.c"); // argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // runs word count
    } else {
        // parent process
        int wc = wait(NULL); // wait for child process to finish and return the child's pid
        printf("wait() return %d\n", wc);
        printf("I am the parent process (pid:%d)\n", (int) getpid());
    }

    return 0;
}