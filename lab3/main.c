/*
 * File:   main.c
 * Author: i4wang
 *
 *
 * Create on January 30, 2024, 10:34 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv)
{
    int flag;
    char command[100];
    char *args[100];
    while (1)
    {
        printf("Your command> ");
        int i = 0;
        int ch;

        // Read the input line
        while ((ch = getchar()) != '\n')
        {
            command[i++] = ch;
        }
        command[i] = '\0'; // end line with \0

        // Check if the last character is '&'
        flag = (command[i - 1] == '&');

        // Parse the command
        char *token = strtok(command, " ");
        i = 0;
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            execvp(args[0], args);
            exit(EXIT_FAILURE);
        }
        else if (!flag) // If not flagged, then parent will wait for child
            { 
                // Parent process
                waitpid(pid, NULL, 0);
            }
    }
    return 0;
}