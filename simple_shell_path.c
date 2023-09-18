#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

char* get_path(char* command) {
    char* path = getenv("PATH");
    char* path_copy = strdup(path);
    char* token = strtok(path_copy, ":");

    while (token != NULL) {
        char* executable = (char*)malloc(strlen(token) + strlen(command) + 2);
        sprintf(executable, "%s/%s", token, command);

        if (access(executable, F_OK) == 0) {
            free(path_copy);
            return executable;
        }

        free(executable);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

int main(void)
{
    const char* prompt = ":) ";
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
            char* executable = get_path(args[0]);

            if (executable == NULL) {
                printf("%s: command not found\n", args[0]);
                continue;
            }

            pid_t pid = fork();

            if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                if (execv(executable, args) == -1) {
                    perror("execv");
                    exit(EXIT_FAILURE);
                }
            } else {
                wait(&status);
            }

            free(executable);
        }
    }

    return 0;
}
