// This code written by Chris Davis

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    int  data;
    struct node *next;
    struct node *prev;
};

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
    
    // Declare variables and pointers
    int i, counter;
    counter = atoi(argv[1]);
    struct node *current, *temp, *head, *tail;
    head = NULL;
    
    // For loop to insert data into linked list
    for(i=0; i < counter; i++)
    {
        printf("Input data:\t%d\n", i);
        if (head == NULL)
        {
            if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL)
            {
                // haven't fixed this yet
                temp->data = i;
                temp->next = NULL;
                temp->prev = NULL;
                current = temp;
                head = temp;
            }
            else
                printf("Memory allocation failed");
        }
        else
        {
            if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL)
            {
                // haven't fixed this yet
                temp->data = i;
                current->next = temp;
                temp->prev = current;
                current = temp;
            }
            else
                printf("Memory allocation failed");
        }
    }
    
    // Set the tail pointer
    tail = current;
    
    // Print blank line
    printf("\n");
    
    // Print the list forwards
    current = head;
    while (current)
    {
        // Print out data, tab delimited
        printf("Left to right output:\t%d\n", current->data);
        current = current->next;
    }
    
    // Print blank line
    printf("\n");
    
    // Print the list backwards
    current = tail;
    while (current)
    {
        // Print out data, tab delimited
        printf("Right to left output:\t%d\n", current->data);
        current = current->prev;
    }
    
    // Free the array(s)
    current = head;
    while (current)
    {
        if (!current->next)
        {
            free(current);
            break;
        }
        current = current->next;
        free(current->prev);
    }
    
    return 0;
}

/*
HW-6	CS230	10 points	Due: June 21

Write a program that builds a doubly linked
linked-list and populate the linked list with
the integers 0 through N (where N is a command
line argument, see
http://gd.tuwien.ac.at/languages/c/programming-bbrown/c_105.htm).
Note that you must trap cases where you have
no command line arguments and where you have too
many command line arguments. It is OK in both of
these cases to print an error message and exit
the program.

Your program must display the value of N (formatted
as shown below - tab seperated) followed by a blank
line. You may also want to "man 3 atoi()".

As you populate the list, print out the values
being inserted (formatted as shown below - tab
seperated), followed by a blank line.

Once the list is populated, print out the
contents from left to right, then print out a
blank line, then print out the contents from
right to left.

The inputs (data or payload) will simply come from
a for loop (0 to N), in that order! Here is what
your output MUST look like (except N will vary).

Command line argument: 	3

Input data:		0
Input data:		1
Input data:		2
Input data:		3

Left to right output:	0
Left to right output:	1
Left to right output:	2
Left to right output:	3

Right to left output:	3
Right to left output:	2
Right to left output:	1
Right to left output:	0

Finally, pictorally, the linked list should look
like this:

Head -> |---| -> |---| -> NULL
        | 0 |    | 1 |
NULL <- |___| <- |___| <- Tail

REQUIREMENTS:
-------------
1. Your program must run in Streibel 109 or on shell.aero.und.edu.

2. Your full name must appear as a comment at the beginning of your
program.

3. Your source code must be named hw6-yourname.c

4. Email your source (subject hw6-yourname) to rmarsh@cs.und.edu and to
ivyjoy.serrano@my.und.edu
*/
