#include <stdio.h>
#include <string.h>

#define COMMAND_LENGTH 200
#define NAME_LENGTH 50

void createFile()
{
    char filename[NAME_LENGTH];

    printf("Enter File name: ");
    fgets(filename, NAME_LENGTH, stdin);

    char command[COMMAND_LENGTH];
    snprintf(command, COMMAND_LENGTH, "touch \"%s\"", filename);

    int status = system(command);

    if (status != -1)
    {
        printf("File Created Successfully\n\n\n");
    }
    else
    {
        printf("Failed Creating File\n");
        printf("Try Again ...\n");
        createFile();
    }
}

void createDirectory()
{
    char dirname[NAME_LENGTH];

    printf("Enter Directory name: ");
    fgets(dirname, NAME_LENGTH, stdin);

    char command[COMMAND_LENGTH];
    snprintf(command, COMMAND_LENGTH, "mkdir -p \"%s\"", dirname);

    int status = system(command);

    if (status != -1)
    {
        printf("Directory Created Successfully\n\n\n");
    }
    else
    {
        printf("Failed Creating Directory\n");
        printf("Try Again ...\n");
        createDirectory();
    }
}