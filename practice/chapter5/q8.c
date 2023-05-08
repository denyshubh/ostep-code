#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t child1, child2;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork first child process
    child1 = fork();

    if (child1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {
        // Child 1 - Writes to the pipe
        close(pipefd[0]);  // Close unused read end

        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]); // Close the write end of the pipe

        execlp("ls", "ls", NULL); // Execute 'ls' command
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Fork second child process
        child2 = fork();

        if (child2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child2 == 0) {
            // Child 2 - Reads from the pipe
            close(pipefd[1]); // Close unused write end

            dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
            close(pipefd[0]); // Close the read end of the pipe

            execlp("sort", "sort", NULL); // Execute 'sort' command
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            close(pipefd[0]);
            close(pipefd[1]);

            wait(NULL); // Wait for first child to finish
            wait(NULL); // Wait for second child to finish

            printf("Parent: Both children finished.\n");
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
