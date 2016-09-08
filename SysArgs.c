//
//  hw1-ChrisDavis.c
//  
//
//  Created by Chris Davis on 9/4/14.
//
//

#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char command[200];
    if (argc == 1) {
        printf("There were no arguments passed!\n");
    } else if (argc == 2) {
        system(argv[1]);
    } else if (argc == 3) {
        strcpy(command, argv[1]);
        strcat(command, " ");
        strcat(command, argv[2]);
        system(command);
    } else if (argc == 4) {
        strcpy(command, argv[1]);
        strcat(command, " ");
        strcat(command, argv[2]);
        strcat(command, " ");
        strcat(command, argv[3]);
        system(command);
    } else if (argc == 5) {
        strcpy(command, argv[1]);
        strcat(command, " ");
        strcat(command, argv[2]);
        strcat(command, " ");
        strcat(command, argv[3]);
        strcat(command, " ");
        strcat(command, argv[4]);
        system(command);
    } else if (argc > 5) {
        printf("There were too many arguments passed!\n");
    }
}