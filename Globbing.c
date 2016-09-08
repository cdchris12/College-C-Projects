// This code created by Chris Davis
// ID Number: 0879026
// Completed on: 11/9/2014

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <regex.h>

struct list {
    char name[100];
    int seq;
};

int main(int argc, char * argv[])
{    
    // <---- Args Checking ---->
    printf("Checking args...\n");
    char name[100];
    int limit = 0;
    char file_name[100];
    
    if (argc == 1) { // No args
        printf("You didn't enter any args. This program requires exactly (2) args. Exiting...\n");
        exit(1);
    } else if (argc == 3) { // 2 args
        strcpy(name, argv[2]);
        
        if (isdigit(argv[1][0])) { // Verify the 1st arg can be converted to a number
            limit = atoi(argv[1]);
        } else {
            printf("The first arg was not a number. Please enter a whole number between 1 and 5000 for the first arg. Exiting...\n");
            exit(1);
        }
        
        if ( (limit < 1) || (limit > 5000) ) { // Number out of established range
            printf("Please enter a whole number between 1 and 5000 for the first arg. Exiting...\n");
            exit(1);
        }
        
    } else { // At least one, but too many or too few args
        printf("You entered %d args. This program requires exactly (2) args. Exiting...\n", argc);
        exit(1);
    }
    printf("Done checking args!!\n");
    // <---- Args Checking ---->
    
    // <---- File Creation ---->
    printf("Creating files...\n");
    int i;
    int hndl;
    int res;
    
    printf("here...\n");
    
    for (i=1; i <= limit; i++){
        //printf("%d", i);
        sprintf(file_name, "%s-%d.junk", name, i);
        //printf(file_name);
        hndl = creat(file_name, S_IREAD | S_IWRITE);
        if (hndl == -1) {
            printf("Error creating data file %s!! Exiting...\n", file_name);
            exit(1);
        } else {
            res = close(hndl);
            if (res == -1) {
                printf("Something went wrong closing the file we just created!! Exiting...\n");
                exit(1);
            }
        }
    }
    printf("Files created!\n");
    // <---- File Creation ---->
    
    // <---- File Listing ---->
    printf("Creating file list...\n");
    struct list file_list[limit*2];
    regex_t regex;
    int reti;
    char msgbuf[100];
    char reg[100];
    
    sprintf(reg, "%s[-][[:digit:]]+\\.junk", name);
    printf("Regex is: %s\n", reg);
    
    reti = regcomp(&regex, reg, REG_EXTENDED); // Compile RegEx
    if (reti){
        printf("Could not compile RegEx!! Exiting...\n");
        exit(1);
    }
    printf("Made the regex!!\n");
    
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    i = 0;
    
    if ((dir = opendir("./")) != NULL) {
        printf("Opened the dir!!\n");
        while ((entry = readdir(dir)) != NULL) { // Print files and directories in cwd
            //printf("Trying to execute a regex...\n");
            reti = regexec(&regex, entry->d_name, 0, NULL, REG_ICASE); // Call RegEx
            printf("String: %s\n", entry->d_name);
            //printf("Executed a regex for item #: %d, with a value of: %d!!\n", i, reti);
        
            if (!reti) { // Match
                strcpy(file_list[i].name, entry->d_name); // Copy the filename to the list struct
                printf("Added %s to the list!!\n", file_list[i].name);
                file_list[i].seq = i; // Add in a sequence number
                i++; // Keep track of how many matches we've found
                printf("Executed a regex for item #: %d, with a value of: %d!!\n", i, reti);
            } else if (reti == REG_NOMATCH) { // No Match
                continue;
            } else { // RegEx error
                printf("Regex match failed!! Exiting...\n");
                exit(1);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        printf("Unable to open the directory!! Exiting...\n");
        exit(1);
    }
    
    int list_length = i;
    
    regfree(&regex);
    printf("List creation complete!\n");
    // <---- File Listing ---->
    
    // <---- List File Creation ---->
    printf("Creating list file...\n");
    
    FILE *list_file = fopen("hw10-ChrisDavis-451.list", "w");
    if (list_file == NULL) {
        printf("Could not create the list file!! Exiting...");
        exit(1);
    }
    
    for (i=0; i<list_length; i++) {
        fprintf(list_file, "%s\t%d\n", file_list[i].name, file_list[i].seq);
    }
    
    fclose(list_file);
    printf("List file created!!\n");
    // <---- List File Creation ---->
    
    // <---- File Deletion ---->
    
    for (i=0; i<list_length; i++) {
        unlink(file_list[i].name);
    }
    //unlink("hw10-ChrisDavis-451.list");
    
    // <---- File Deletion ---->
}

// Thread psuedocode:
//		sem_wait (&mutex);
//		(Do work)
//		sem_post (&mutex);


/*
HW-10	CS451	10 points	Due: Monday, December 1

Write a program that globs:

Wildcard arguments to a command may be expanded by the
shell (Bash, etc) before the command executes. This is
referred to as "globbing".
 
So, when you do something like "ls *", what happens is
that the shell expands the "*" to all entries in the
current directory. Thus, "ls *" really becomes: 

ls file1,file2, file3, ... fileN 

and if the string length of file1 to fileN is too large, 
you get an argument-list-too-long-error.

On some operating systems the argument length has recently 
been extended, thus some commands no longer have this 
problem. Yet, some still do.

1. Create a program that uses command-line arguments (argv, 
   argc) to specify the number of files to create and the
   base filename (ie ./h10 5000 stuff <-- note the order). 

2. Have your program create the specified number of files. 
   Given the above command-line example, you would create
   5000 files with the naming convention "stuff-N.junk"; 
   where N ranges from 1 to 5000. You MUST use creat() to 
   create the files.

3. You must create a list of the created files. The list 
   must contain the filename and some sequence number 
   (1-5000 for our example). This list must be a two column 
   list (tab separated). You must use opendir(), readdir(), 
   etc to read the directory and create the list. You must
   write your list to the drive and the list must be named 
   "hw10-yourname-451.list"

4. Clean up the mess you made. You must use unlink() to 
   delete the created files. Note that there will be other 
   files in the directory called "stuff". Thus, you must be 
   very precise in how you remove your created files (simply 
   using a wildcard will not work!).

REQUIREMENTS:
-------------
1. Your program must run in Streibel 109/115.

2. Your full name must appear as a comment at the beginning of your 
   program.

3. Your source code must be named hw10-yourname.c or hw10-yourname.cpp

4. Email your source (subject hw10-yourname) to rmarsh@cs.und.edu
*/