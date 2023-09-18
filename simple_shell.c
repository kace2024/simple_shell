#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
    const char* prompt = "#cisfun$ ";
    char buffer[BUFFER_SIZE];
    char* command;
    int status;

    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character

        if (strcmp(buffer, "exit") == 0)
            break;

        command = strtok(buffer, " ");

        if (command != NULL) {
            pid_t pid = fork();

            if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                if (execlp(command, command, NULL) == -1) {
                    perror("execlp");
                    exit(EXIT_FAILURE);
                }
            } else {
                wait(&status);
            }
        }
    }

    return 0;
}
