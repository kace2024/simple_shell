#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    int status;

    while (1) {
        printf("$ ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Tokenize the command into arguments
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGUMENTS - 1) {
            arguments[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        arguments[i] = NULL;

        // Fork a child process to execute the command
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execvp(arguments[0], arguments);
            perror("Exec failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
