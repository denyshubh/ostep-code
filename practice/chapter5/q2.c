#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>

int
main (int args, char *argv[]) {
    
    int fd = open("q2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    if (fd < 0) {
        fprintf(stderr, "open failed\n");
        exit(1);
    }

    int rc = fork();    // creating a child process
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {   // child process
        char child_msg[100];
        sprintf(child_msg, "Child process %d is writing to the file...\n", (int) getpid());
        write(fd, child_msg, strlen(child_msg));

    } else {    // parent process
        wait(NULL);    // wait for child process to finish and return the child's pid
        char parent_msg[100];
        sprintf(parent_msg, "Parent process %d is writing to the file...\n", (int) getpid());
        write(fd, parent_msg, strlen(parent_msg));

    }

    // Close the file descriptor
    close(fd);
    
    return 0;
}