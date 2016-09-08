// This code written by Chris Davis

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <dlfcn.h>
#include "./hw9-lib-chrisdavis.h"

extern struct node {
    int  data;
    struct node *next;
    struct node *prev;
};

struct node *trashTail, *trashHead, *trashCurrent;

int trashSize = 0;

int main( int argc, char *argv[] )
{
    // Implement and check command line arguments
    if( argc == 2 )
        printf("Command line argument:\t%s\n\n", argv[1]);
    else if( argc > 2 )
    {
        printf("Too many arguments supplied.\n");
        return 1;
    }
    else
    {
        printf("One argument expected.\n");
        return 2;
    }
    
    // Get all the functions from the Shared Library
    void * handle;
    
    void (*DisplayInorder)(struct node *);
    void (*DisplayPostorder)(struct node *);
    void (*DisplayTrash)(struct node *);
    void (*FreeInorder)(struct node *);
    void (*FreeTrash)(struct node *);
    void (*AddToTrash)(struct node *, struct node *, int);
    
    handle = dlopen("./libhw9-lib-chrisdavis.so", RTLD_LAZY|RTLD_GLOBAL);
    if (!handle)
        printf("%s\n", dlerror());
    DisplayInorder = dlsym(handle, "DisplayInorder");
    DisplayPostorder = dlsym(handle, "DisplayPostorder");
    DisplayTrash = dlsym(handle, "DisplayTrash");
    FreeInorder = dlsym(handle, "FreeInorder");
    FreeTrash = dlsym(handle, "FreeTrash");
    AddToTrash = dlsym(handle, "AddToTrash");
    
    // Declare variables and pointers
    int i, counter, removal;
    counter = atoi(argv[1]);
    struct node *current, *temp, *head, *tail;
    head = NULL;
    
    // For loop to insert data into linked list
    for(i=0; i <= counter; i++)
    {
        printf("Input data:\t%d\n", i);
        if (head == NULL)
        {
            if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL)
            {
                temp->data = i;
                temp->next = NULL;
                temp->prev = NULL;
                current = temp;
                head = temp;
            }
            else
            {
                printf("Memory allocation failed");
                return 1;
            }
        }
        else
        {
            if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL)
            {
                temp->data = i;
                current->next = temp;
                temp->prev = current;
                current = temp;
            }
            else
            {
                printf("Memory allocation failed");
                return 1;
            }
        }
    }
    
    // Set the tail pointer
    tail = current;
    
    // Print blank line
    printf("\n");
    
    // Print the list forwards
    (*DisplayInorder)(head);
    
    // Print blank line
    printf("\n");
    
    // Print the list backwards
    (*DisplayPostorder)(tail);
    
    // Determine how many and which nodes to put into Trashcan
    removal = rand() % counter + 3;
    for (i = 0; i <= removal; i++)
    {
        // Pick a random node (payload) to delete.
        removal = (rand() % counter);
        
        //printf("%d\n", removal);
        
        // Find the specified payload in the linked list
        current = head;
        while (current)
        {
            if (current->data == removal)
            {
                if (current->prev == NULL)
                {
                    // Set the next node in the linked list to head
                    current->next->prev = NULL;
                    head = current->next;
                    
                    // Do something to put the node current into the Trash linked list
                    ((*AddToTrash)(current, trashHead, trashSize));
                    trashSize++;
                    printf("I just changed the head");
                    break;
                }
                
                else
                {
                    // Change prev and next pointers to exclude this node
                    if (current->next != NULL)
                    {
                        current->next->prev = current->prev;
                        current->prev->next = current->next;
                    }
                    
                    // Drop the pointers to the current node, as it is at the tail of the linked list
                    else // (current->next == NULL)
                    {
                        current->prev->next = NULL;
                    }
                    
                    //Do something to put the node current into the Trash linked list
                    printf("I just sent %d to trash.\n", removal);
                    ((*AddToTrash)(current, trashHead, trashSize));
                    trashSize++;
                    break;
                }
            }
            
            else if (current->next != NULL)
                current = current->next;
            
            else
            {
                //printf("Either something went REALLY wrong, or this number was selected twice. The number selected was %d.\n", removal);
                break;
                // current = current->next;
            }
        }
    }
    
    // Display the trash linked list
    (*DisplayTrash)(trashHead);
    
    // Free the trash linked list
    //FreeTrash(trashHead);
    
    // Print blank line
    printf("\n");
    
    // Print the list forwards
    (*DisplayInorder)(head);
    
    // Print blank line
    printf("\n");
    
    // Print the list backwards
    (*DisplayPostorder)(tail);
    
    // Free the array(s)
    (*FreeInorder)(head);
    
    // Free the opened shared library
    dlclose(handle);
    
    return 0;
}

/*
 HW-9-b	CS230		30 points	Due: July 11
 
 For this assignment you will divide HW-7 and develop a
 Makefile to practice using the compiler and linker with
 libraries. All files will be strictly C code - no C++!
 
 Part 1 (5 points):
 ------------------
 Seperate HW-7 into two parts (2 files):
 1. The MAIN routine (call this file hw9-yourname.c).
 2. The functions (call this file hw9-lib-yourname.c).
 
 Write an associated header file for the functions
 (call this file hw9-lib-yourname.h)
 
 Write a Makefile that compiles and links the above in 2!!!
 steps. You MUST call this Makefile "Makefile1".
 
 Part 2 (5 points):
 ------------------
 Write a Makefile that creates a STATIC library
 (hw9-lib-yourname.a) out of the hw9-lib-yourname.c file
 and that compiles and links hw9-yourname.c with your
 static library. You MUST call this Makefile "Makefile2".
 
 Part 3 (5 points):
 ------------------
 Write a Makefile that creates a SHARED library
 (hw9-lib-yourname.so) out of the hw9-lib-yourname.c file
 and that compiles and links hw9-yourname.c with your
 shared library. You MUST call this Makefile "Makefile3".
 
 Part 4 (15 points):
 -------------------
 Modify the hw9-yourname.c to use the SHARED library
 (hw9-lib-yourname.so) dynamically (using dlopen). Call
 this MAIN program hw9-yourname-4.c. This code must make
 use of all 4 related functions (dlopen, dlclose, dlerror
 and dlsym).
 
 Write a Makefile that compiles and links hw9-yourname-4.c
 with your dynamic shared library. You MUST call this
 Makefile "Makefile4".
 
 REQUIREMENTS:
 -------------
 1. Your program must run in Streibel 109 or on shell.aero.und.edu.
 
 2. Your full name must appear as a comment at the beginning of your
 program.
 
 3. Your source code must be tarballed and named hw9-yourname.tar
 
 4. Email your source (subject hw9-yourname) to rmarsh@cs.und.edu and to
 ivyjoy.serrano@my.und.edu
 
 
 * Submissions that do not follow the above requirements will
 NOT be graded and will receive 0 points.
 
 */