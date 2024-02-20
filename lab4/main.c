/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: i4wang
 *
 * Created on February 11, 2024, 5:27 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char input[100];
    char cmd1[100];
    char cmd2[100];
    int flag = 0;
    int j = 0;
    int k = 0;

    printf("Your command> ");
    fgets(input, 100, stdin);

    // Parse the input
    for (int i = 0; i < strlen(input) - 1; i++)
    {
        if (input[i] == '|')
        {
            flag = 1;
            i++;
        }
        else if (input[i] != '|' && flag == 0)
        {
            cmd1[j] = input[i];
            j++;
        }
        else
        {
            cmd2[k] = input[i];
            k++;
        }
    }

    int pipefd[2];
    pipe(pipefd);

    if (fork() == 0)
    { // child process
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        system(cmd1); // execute second command
        exit(0);
    }
    else
    { // parent process
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        system(cmd2); // execute first command
    }
    return 0;
}
