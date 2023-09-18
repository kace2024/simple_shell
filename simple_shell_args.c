#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

int main(void)
{
    const char* prompt = "#cisfun$ ";
    char buffer[BUFFER_SIZE];
    char* command;
    char* args[MAX_ARGS];
    int status;

    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character

        if (strcmp(buffer, "exit") == 0)
            break;

        command = strtok(buffer, " ");
        int i = 0;
        while (command != NULL && i < MAX_ARGS - 1) {
            args[i++] = command;
            command = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] != NULL) {
            pid_t pid = fork();

            if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                if (execvp(args[0], args) == -1) {
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
            } else {
                wait(&status);
            }
        }
    }

    return 0;
}
