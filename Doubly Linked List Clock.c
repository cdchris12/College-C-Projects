// This code written by Chris Davis

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct node {
    int  payload;
    struct node *next;
    struct node *prev;
}*head, *tail, *current, *temp;

int i;

void Inorder (struct node *current); // Prototype

void Postorder (struct node *current); // Prototype

void FreeInorder (struct node *current); // Prototype

void Add (int i); // Prototype

void Set (int counter); // Prototype

int main( int argc, char *argv[] )
{
    // Print my name, to avoid code theft
    printf("This code written by: Chris Davis\n\n");

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
    int counter;
    counter = atoi(argv[1]);
    head = NULL;
    tail = NULL;
    current = NULL;
    temp = NULL;

    
    // For loop to insert data into linked list
    for(i=1; i < 13; i++)
    {
        Add(i);
    }
    
    // Print blank line
    printf("\n");
    
    // Print the list forwards
    Inorder(head);
    
    // Print blank line
    printf("\n");
    
    // Print the list backwards
    Postorder(tail->prev);
    
    // Print blank line
    printf("\n");

    // Set the clock
    Set(counter);

    // Print blank line
    printf("\n");
    
    // Print the list forwards
    Inorder(head);
    
    // Print blank line
    printf("\n");
    
    // Print the list backwards
    Postorder(tail->prev);
    
    // Free the array(s)
    //FreeInorder(head);
    
    return 0;
}

void Set (int counter)
{
    // Traverse the list, looking for our specified time
    while (current->payload != counter)
    {
	current = current->next;
    }

    // Set the "top" of the clock to counter
    head = current;
    tail = current;
}

void Add (int i)
{
    printf("Input data:\t%d\n", i);
    if (head == NULL)
    {
        if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL)
        {
            temp->payload = i;
            temp->next = NULL;
            temp->prev = NULL;
            current = temp;
            head = temp;
	    tail = temp;
        }
        else
        {
            printf("Memory allocation failed");
            //return 1;
        }
    }
    else
    {
        if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL)
        {
            temp->payload = i;
            current->next = temp;
            temp->prev = current;
            current = temp;
        }
        else
        {
            printf("Memory allocation failed");
            //return 1;
        }
    }

    // Link the two ends of the doubly linked list
    if (i == 12)
    {
	head->prev = current;
	current->next = head;
    }
}

void Inorder (struct node *current)
{
    // Print the list forwards
    for(i=0;i<15;i++)
    {
        printf("ClockWise output:\t%d\n", current->payload);
    	current = current->next;
    }
}

void Postorder (struct node *current)
{
    // Print the list forwards
    int i;
    for(i=0;i<15;i++)
    {
        printf("CounterClockWise output:\t%d\n", current->payload);
    	current = current->prev;
    }
}



void FreeInorder (struct node *current)
{
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
}


// Beginning of the sample output

/*
bash-4.1$ ./a.out 6
This code written by: Chris Davis

Command line argument:	6

Input data:	1
Input data:	2
Input data:	3
Input data:	4
Input data:	5
Input data:	6
Input data:	7
Input data:	8
Input data:	9
Input data:	10
Input data:	11
Input data:	12

ClockWise output:	1
ClockWise output:	2
ClockWise output:	3
ClockWise output:	4
ClockWise output:	5
ClockWise output:	6
ClockWise output:	7
ClockWise output:	8
ClockWise output:	9
ClockWise output:	10
ClockWise output:	11
ClockWise output:	12
ClockWise output:	1
ClockWise output:	2
ClockWise output:	3

CounterClockWise output:	12
CounterClockWise output:	11
CounterClockWise output:	10
CounterClockWise output:	9
CounterClockWise output:	8
CounterClockWise output:	7
CounterClockWise output:	6
CounterClockWise output:	5
CounterClockWise output:	4
CounterClockWise output:	3
CounterClockWise output:	2
CounterClockWise output:	1
CounterClockWise output:	12
CounterClockWise output:	11
CounterClockWise output:	10


ClockWise output:	6
ClockWise output:	7
ClockWise output:	8
ClockWise output:	9
ClockWise output:	10
ClockWise output:	11
ClockWise output:	12
ClockWise output:	1
ClockWise output:	2
ClockWise output:	3
ClockWise output:	4
ClockWise output:	5
ClockWise output:	6
ClockWise output:	7
ClockWise output:	8

CounterClockWise output:	5
CounterClockWise output:	4
CounterClockWise output:	3
CounterClockWise output:	2
CounterClockWise output:	1
CounterClockWise output:	12
CounterClockWise output:	11
CounterClockWise output:	10
CounterClockWise output:	9
CounterClockWise output:	8
CounterClockWise output:	7
CounterClockWise output:	6
CounterClockWise output:	5
CounterClockWise output:	4
CounterClockWise output:	3
*/
