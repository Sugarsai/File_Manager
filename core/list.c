#include <stdio.h>
#include <string.h>

#define COMMAND_LENGTH 200
#define NAME_LENGTH 50

void listFiles()
{
    int status = system("ls -l | grep '^-'");

    if (status == -1)
    {
        printf("Failed to execute command\n");
    }
}

void listDirectories()
{
    int status = system("ls -l | grep '^d'");

    if (status == -1)
    {
        printf("Failed to execute command\n");
    }
}