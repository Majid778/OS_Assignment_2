#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int num_processes = 5;

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            printf("Error: fork() failed\n");
            exit(1);
        }
        else if (pid == 0) {
            // child process
            printf("Child process %d with PID %d and parent %d\n", i, getpid(), getppid());
            exit(0);
        }
        else {
            // parent process
            // printf("Parent process with PID %d created child process %d with PID %d\n", getpid(), i, pid);
        }
    }

    // wait for all child processes to finish
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    return 0;
}