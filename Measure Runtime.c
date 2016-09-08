// This code written by Chris Davis

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct timeval begin, end;

struct node {
    int  data;
    struct node *next;
    struct node *prev;
}*trashHead, *trashTail, *trashCurrent;

struct timeNode {
    double  data;
    struct timeNode *next;
    struct timeNode *prev;
}*timeHead, *timeTail, *timeCurrent;

// initalize variables to keep track of K best measurement bounds
int flag = 0, K = 3, M = 1000;
double e = 0.001;

void DisplayInorder (struct node *head1); // Prototype

void DisplayPostorder (struct node *tail1); // Prototype

void DisplayTrash (struct node *trashHead1); // Prototype

void FreeInorder (struct node *head2); // Prototype

void FreeTrash (struct node *trashHead2); // Prototype

int AddToTrash (struct node *toTrash, int trashSize1); // Prototype

int AddToTime (double elapsed1, int timeLength1); // Prototype

int main( int argc, char *argv[] )
{
    // initalize variables to keep track of K best measurement bounds
    int f;
    int timeLength = 0;
    
    // For loop to measure iterations of K best measurements
    for (f = 0; f < M; f++)
    {
        // Get beginning runtime of program
        gettimeofday(&begin, NULL);
        
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
        int i, counter, removal, trashSize = 0;
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
        DisplayInorder(head);
        
        // Print blank line
        printf("\n");
        
        // Print the list backwards
        DisplayPostorder(tail);
        
        // Determine how many and which nodes to put into Trashcan
        removal = rand() % counter + 3;
        for (i = 0; i < removal; i++)
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
                        trashSize = AddToTrash(current, trashSize);
                        printf("I just changed the head\n");
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
                            tail = current->prev;
                            printf("I just changed the tail\n");
                        }
                        
                        //Do something to put the node current into the Trash linked list
                        printf("I just sent %d to trash.\n", removal);
                        trashSize = AddToTrash(current, trashSize);
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
        DisplayTrash(trashHead);
        
        // Free the trash linked list
        //FreeTrash(trashHead);
        
        // Print blank line
        printf("\n");
        
        // Print the list forwards
        DisplayInorder(head);
        
        // Print blank line
        printf("\n");
        
        // Print the list backwards
        DisplayPostorder(tail);
        
        // Free the array(s)
        FreeInorder(head);
        
        // Print blank line
        printf("\n");
        
        // Get time for end of execution
        gettimeofday(&end, NULL);
        
        // Calculate the difference between beginning time and end time
        double elapsed = ((end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0));
        
        // Pass elapsed time to a function
        timeLength = AddToTime(elapsed, timeLength);
        
        if (flag)
        {
            return 3;
        }
        
        //printf("%d", f);
        
        // Print the difference to the standard output
        //printf("The calculations took %f seconds.\n", elapsed);
    } // End of K measurement for loop
    
    return 0;
}

void DisplayInorder (struct node *head1)
{
    // Print the list forwards
    while (head1)
    {
        // Print out data, tab delimited
        printf("Left to right output:\t%d\n", head1->data);
        head1 = head1->next;
    }
}

void DisplayPostorder (struct node *tail1)
{
    while (tail1)
    {
        // Print out data, tab delimited
        printf("Right to left output:\t%d\n", tail1->data);
        tail1 = tail1->prev;
    }
}

int AddToTrash (struct node *toTrash, int trashSize1)
{
    //struct node *trashCurrent;
    
    if (trashSize1 == 0)
    {
        trashHead = toTrash;
        trashCurrent = toTrash;
        trashTail = toTrash;
        toTrash->prev = NULL;
        toTrash->next = NULL;
        trashSize1++;
    }
    
    else
    {
        toTrash->next = NULL;
        trashCurrent->next = toTrash;
        toTrash->prev = trashCurrent;
        trashCurrent = trashCurrent->next;
        trashTail = trashCurrent;
        trashSize1++;
    }
    
    return trashSize1;
    
}

void DisplayTrash (struct node *trashHead1)
{
    // Print the trash list forwards
    while (trashHead1)
    {
        // Print out data, tab delimited
        printf("Trash output:\t%d\n", trashHead1->data);
        if (!trashHead1->next)
        {
            free(trashHead1);
            break;
        }
        trashHead1 = trashHead1->next;
        free(trashHead1->prev);
    }
}

void FreeTrash (struct node *trashHead2)
{
    while (trashHead2)
    {
        if (!trashHead2->next)
        {
            free(trashHead2);
            break;
        }
        trashHead2 = trashHead2->next;
        free(trashHead2->prev);
    }
}

void FreeInorder (struct node *head2)
{
    while (head2)
    {
        if (!head2->next)
        {
            free(head2);
            break;
        }
        head2 = head2->next;
        free(head2->prev);
    }
}

int AddToTime (double elapsed1, int timeLength1)
{
    double temp;
    int q;
    if (timeLength1 == 0) // Inserting the first node
    {
        if ((timeCurrent = (struct timeNode *)malloc(sizeof(struct timeNode))) != NULL)
        {
            timeCurrent->data = elapsed1;
            timeCurrent->next = NULL;
            timeCurrent->prev = NULL;
            timeHead = timeCurrent;
            timeTail = timeCurrent;
            timeLength1 = 1;
        }
        else
        {
            printf("Memory allocation failed");
            flag = 1;
            return 1;
        }
    }
    
    else // Inserting another node at the end of the list
    {
        if ((timeCurrent = (struct timeNode *)malloc(sizeof(struct timeNode))) != NULL)
        {
            timeCurrent->data = elapsed1;
            timeCurrent->next = NULL;
            timeCurrent->prev = timeTail;
            timeTail->next = timeCurrent;
            timeTail = timeCurrent;
            timeLength1++;
        }
        else
        {
            printf("Memory allocation failed");
            flag = 1;
            return 1;
        }
    }
    
    // Sort the list
    timeCurrent = timeHead;
    while (timeCurrent->next)
    {
        if (timeCurrent->data < timeCurrent->next->data)
        {
            temp = timeCurrent->next->data;
            timeCurrent->next->data = timeCurrent->data;
            timeCurrent->data = temp;
        }
        
        else
            timeCurrent = timeCurrent->next;
    }
    
    // Compare values to evaluate if we have met the K requirement
    timeCurrent = timeTail;
    if (timeLength1 > 3)
    {
        if((timeCurrent->prev->data - timeCurrent->data) < e)
        {
            if((timeCurrent->prev->prev->data - timeCurrent->data) < e)
            {
                if((timeCurrent->prev->prev->prev->data - timeCurrent->data) < e)
                {
                    printf("The measurements have converged at %f! It took all of %d iterations of the program's code to come up with that figure. ", timeCurrent->data, timeLength1);
                    flag = 1;
                    double timeTotal = 0;
                    timeCurrent = timeHead;
                    while (timeCurrent)
                    {
                        timeTotal = (timeTotal + timeCurrent->data);
                        
                        if (!timeCurrent->next)
                        {
                            free(timeCurrent);
                            break;
                        }
                        timeCurrent = timeCurrent->next;
                        free(timeCurrent->prev);
                    }
                    printf("The total runtime of the garbage collection algorithm was %f seconds, by the way.\n", timeTotal);
                    return;
                }
            }
        }
    }
    
    if (timeLength1 >= M)
    {
        double timeTotal = 0;
        timeCurrent = timeHead;
        while (timeCurrent)
        {
            timeTotal = (timeTotal + timeCurrent->data);
            if (!timeCurrent->next)
            {
                free(timeCurrent);
                break;
            }
            timeCurrent = timeCurrent->next;
            free(timeCurrent->prev);
        }
        printf("We couldn't get a definitive convergence value. Sad day. The total runtime of the garbage collection algorithm was %f seconds, by the way.\n", timeTotal);
    }
    
    return timeLength1;

}










/*
HW-8	CS230	10 points	Due: July 3

Modify HW7 such that you can measure the run-time
of the program.

Use the cycle-based gettimeofday K-best method with
K, e, M. Set K to 3. Set M to 1000. Set e to 0.001.

You code should automatically perform the K-best
method and print out the results.

NOTE:
-----
I leave it to you to figure out what results should
be displayed to convince me that your program performed.


REQUIREMENTS:
-------------
1. Your program must run in Streibel 109 or on shell.aero.und.edu.

2. Your full name must appear as a comment at the beginning of your
program.

3. Your source code must be named hw8-yourname.c

4. Email your source (subject hw8-yourname) to rmarsh@cs.und.edu and to
ivyjoy.serrano@my.und.edu
*/