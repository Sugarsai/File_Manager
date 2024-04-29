#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create.c"
#include "delete.c"
#include "list.c"
#include "permissions.c"
// #include "symbolic.c"

int main()
{
    int choice;

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
        // printf("8. Create Symbolic link file");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            listFiles();
            break;
        case 2:
            listDirectories();
            break;
        case 3:
            changePermissions();
            break;
        case 4:
            createFile();
            break;
        case 5:
            createDirectory();
            break;
        case 6:
            deleteFile();
            break;
        case 7:
            deleteDirectory();
            break;
        // case 8:
        // createSymbolic();
        // break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 0 and 7.\n");
        }
    } while (choice != 0);

    return 0;
}