#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COMMAND_LENGTH 200
#define NAME_LENGTH 50

void listFiles(const char *directory);
void listDirectories(const char *directory);
void createFile(const char *directory);
void createDirectory(const char *directory);
void deleteFile(const char *directory);
void deleteDirectory(const char *directory);
void changePermissions(const char *directory);
void createSymbolicLink();

int main()
{
    int choice;
    char directory[NAME_LENGTH];

    printf("Enter the directory path: ");
    fgets(directory, sizeof(directory), stdin);
    directory[strcspn(directory, "\n")] = '\0';

    do
    {
        printf("\nFile Manager Menu\n");
        printf("1. List Files\n");
        printf("2. List Directories\n");
        printf("3. Change Permissions\n");
        printf("4. Create File\n");
        printf("5. Create Directory\n");
        printf("6. Delete File\n");
        printf("7. Delete Directory\n");
        printf("8. Create Symbolic link file\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            listFiles(directory);
            break;
        case 2:
            listDirectories(directory);
            break;
        case 3:
            changePermissions(directory);
            break;
        case 4:
            createFile(directory);
            break;
        case 5:
            createDirectory(directory);
            break;
        case 6:
            deleteFile(directory);
            break;
        case 7:
            deleteDirectory(directory);
            break;
        case 8:
            createSymbolicLink(directory);
            break;
        case 0:
            printf("Ending program..\nbye!\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 0 and 8.\n");
        }
    } while (choice != 0);

    return 0;
}

void listFiles(const char *directory)
{
    char command[COMMAND_LENGTH];
    FILE *fp;
    int file_count;

    snprintf(command, COMMAND_LENGTH, "ls -l \"%s\" | grep '^-' | wc -l", directory);
    fp = popen(command, "r");
    if (fp == NULL)
    {
        printf("Failed to execute command\n");
        return;
    }

    fscanf(fp, "%d", &file_count);
    pclose(fp);

    if (file_count == 0)
    {
        printf("There are no files.");
        return;
    }

    snprintf(command, COMMAND_LENGTH, "ls -l \"%s\" | grep '^-'", directory);
    system(command);
}

void listDirectories(const char *directory)
{
    char command[COMMAND_LENGTH];
    FILE *fp;
    int dir_count;

    snprintf(command, COMMAND_LENGTH, "ls -l \"%s\" | grep '^d' | wc -l", directory);
    fp = popen(command, "r");
    if (fp == NULL)
    {
        printf("Failed to execute command\n");
        return;
    }

    fscanf(fp, "%d", &dir_count);
    pclose(fp);

    if (dir_count == 0)
    {
        printf("There are no directories.");
        return;
    }

    snprintf(command, COMMAND_LENGTH, "ls -l \"%s\" | grep '^d'", directory);
    system(command);
}

void createFile(const char *directory)
{
    char filename[NAME_LENGTH];

    printf("\nEnter File name: ");
    fgets(filename, NAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    if (access(filename, F_OK) != -1)
    {
        printf("File '%s' already exists.\n", filename);
        printf("Please choose a different name.\n\n");
        return;
    }

    char command[COMMAND_LENGTH];
    snprintf(command, COMMAND_LENGTH, "touch \"%s/%s\"", directory, filename);

    int status = system(command);

    if (status != -1)
    {
        printf("File Created Successfully.\n\n\n");
    }
    else
    {
        printf("Failed Creating File\n");
        printf("Try Again ...\n");
        createFile(directory);
    }

    int choice = 1;
    printf("\nDo you want to create another file? (1 for yes, 0 for no): ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        getchar();
        createFile(directory);
    }
    else if (choice == 0)
    {
        printf("\n");
    }
}

void createDirectory(const char *directory)
{
    char dirname[NAME_LENGTH];

    printf("\nEnter Directory name: ");
    fgets(dirname, NAME_LENGTH, stdin);
    dirname[strcspn(dirname, "\n")] = '\0';

    if (access(dirname, F_OK) != -1)
    {
        printf("directory '%s' already exists.\n", dirname);
        printf("Please choose a different name.\n\n");
        return;
    }

    char command[COMMAND_LENGTH];
    snprintf(command, COMMAND_LENGTH, "mkdir -p \"%s/%s\"", directory, dirname);

    int status = system(command);

    if (status != -1)
    {
        printf("Directory Created Successfully.\n\n\n");
    }
    else
    {
        printf("Failed Creating Directory\n");
        printf("Try Again ...\n");
        createDirectory(directory);
    }
    int choice = 1;
    printf("\nDo you want to create another directory? (1 for yes, 0 for no): ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        getchar();
        createDirectory(directory);
    }
    else if (choice == 0)
    {
        printf("\n");
    }
}

void deleteFile(const char *directory)
{
    char filename[NAME_LENGTH];

    printf("\nEnter file name to delete: ");
    fgets(filename, NAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    char command[COMMAND_LENGTH];
    snprintf(command, COMMAND_LENGTH, "rm \"%s/%s\"", directory, filename);

    int status = system(command);

    if (status != -1)
    {
        printf("File Deleted Successfully.\n\n\n");
    }
    else
    {
        printf("File '%s' Doesn't exist.\n", filename);
    }

    int choice = 1;
    printf("\nDo you want to delete another file? (1 for yes, 0 for no): ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        getchar();
        deleteFile(directory);
    }
    else if (choice == 0)
    {
        printf("\n");
    }
}

void deleteDirectory(const char *directory)
{
    char dirname[NAME_LENGTH];

    printf("\nEnter Directory name to delete: ");
    fgets(dirname, NAME_LENGTH, stdin);
    dirname[strcspn(dirname, "\n")] = '\0';

    char command[COMMAND_LENGTH];
    snprintf(command, COMMAND_LENGTH, "rmdir \"%s/%s\"", directory, dirname);

    int status = system(command);

    if (status != -1)
    {
        printf("Directory Deleted successfully.\n\n\n");
    }
    else
    {
        printf("Error Deleting directory '%s'.\n", dirname);
    }
    int choice = 1;
    printf("\nDo you want to delete another directory? (1 for yes, 0 for no): ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        getchar();
        deleteDirectory(directory);
    }
    else if (choice == 0)
    {
        printf("\n");
    }
}

void changePermissions(const char *directory)
{
    char filename[NAME_LENGTH];
    char command[COMMAND_LENGTH];
    char permission[NAME_LENGTH];
    char confirm[10];
    int choice = 1;

    while (choice)
    {
        printf("\nEnter the filename: ");
        fgets(filename, NAME_LENGTH, stdin);
        filename[strcspn(filename, "\n")] = '\0';

        snprintf(command, COMMAND_LENGTH, "test -e \"%s/%s\" && echo \"File exists\" || echo \"File does not exist\"", directory, filename);
        if (system(command) != 0)
        {
            printf("File '%s' does not exist.\n", filename);
            printf("Please enter another filename or 0 to return to the menu: ");
            fgets(confirm, sizeof(confirm), stdin);
            sscanf(confirm, "%d", &choice);
            continue;
        }

        printf("The permissions of file '%s' are:\n", filename);
        snprintf(command, COMMAND_LENGTH, "stat -c '%%A' \"%s/%s\"", directory, filename);
        system(command);

        printf("\nDo you want to change or remove permissions of the file? (yes/no): ");
        fgets(confirm, sizeof(confirm), stdin);
        confirm[strcspn(confirm, "\n")] = '\0';

        if (strcmp(confirm, "yes") == 0 || strcmp(confirm, "Yes") == 0 || strcmp(confirm, "y") == 0 || strcmp(confirm, "Y") == 0)
        {
            printf("\nr : read\nw : write\nx : execute\n(e.g., u+rw, g-w, a+x, -r, -w, -x):\n");
            printf("Enter the new permissions: ");
            fgets(permission, NAME_LENGTH, stdin);
            permission[strcspn(permission, "\n")] = '\0';

            snprintf(command, COMMAND_LENGTH, "chmod %s \"%s/%s\"", permission, directory, filename);
            int status = system(command);

            if (status == 0)
            {
                printf("Permissions changed successfully for file '%s'.\n", filename);
            }
            else
            {
                printf("Failed to change permissions for file '%s'.\n", filename);
            }
        }
        else
        {
            printf("Permission change canceled.\n");
        }

        printf("\nDo you want to operate on another file? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
        getchar();
    }
}

void createSymbolicLink()
{
    char sourcefile[NAME_LENGTH];
    char target[NAME_LENGTH];
    char command[COMMAND_LENGTH];
    char link[NAME_LENGTH];
    char dir[NAME_LENGTH];

    printf("Enter the sourcefile path:\n");
    scanf("%s", sourcefile);

    char confirm;
    printf("Do you want to create symlink in another directory? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y')
    {
        printf("Enter the directory path:\n");
        scanf("%s", dir);

        printf("\nEnter the symbolic link name:\n");
        scanf("%s", target);
        snprintf(command, COMMAND_LENGTH, "cd \"%s\" && ln -s \"%s\" \"%s\"", dir, sourcefile, target);
    }
    else
    {
        printf("Enter the symbolic link name:\n");
        scanf("%s", target);
        snprintf(command, COMMAND_LENGTH, "ln -s \"%s\" \"%s\"", sourcefile, target);
    }

    int status = system(command);

    if (status == 0)
    {
        printf("Symbolic link created successfully\n");
    }
    else
    {
        printf("Failed to create symbolic link\n");
        printf("Try Again..\n");
    }
    int choice = 1;
    printf("\nDo you want to create another symlink? (1 for yes, 0 for no): ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1)
    {
        getchar();
        createSymbolicLink();
    }
    else if (choice == 0)
    {
        printf("\n");
    }
}