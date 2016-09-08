// This code written by Chris Davis

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct node {
    int  data;
    struct node *next;
    struct node *prev;
}*trashHead, *trashTail, *trashCurrent;

void DisplayInorder (struct node *head1); // Prototype

void DisplayPostorder (struct node *tail1); // Prototype

void DisplayTrash (struct node *trashHead1); // Prototype

void FreeInorder (struct node *head2); // Prototype

void FreeTrash (struct node *trashHead2); // Prototype

int AddToTrash (struct node *toTrash, int trashSize1); // Prototype

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


/*
 HW-7	CS230	40 points	Due: June 28
 
 It's time to �take out the garbage.�
 
 The assignment is to modify hw7 such that link removal
 is managed by your own garbage collection system.
 
 Part 1:
 -------
 You MUST modify your hw7 such that the code for displaying
 the list contents is now contained in two functions called:
 
 DISPLAY_INORDER(xxxx)
 DISPLAY_POSTORDER(xxxx)
 
 Where xxxx will be whatever parameters need to be passed.
 
 You MUST also have a routine that deletes (frees) the nodes
 of the link list. This routine will get called at the end
 of the program. The function will be called:
 
 FREE_INORDER(xxxx)
 
 Part 2:
 -------
 You must now randomly determine a number of nodes to delete
 and randomly determine what specific nodes to delete. You
 might want to use something like:
 
 number2Delete = rand() % number2Add + 3;
 for (i = 0; i < number2Delete; i++) {
 // Pick a random node (payload) to delete.
 link2Delete = (rand() % number2Add);
 
 Part 3:
 -------
 For each node selected for removal, you must not yet actually
 delete it from memory. Rather you will adjust your linked list
 to skip over it and use a second linked list (your trash list) to
 record the node slated for deletion. You must also account for
 the case where an already deleted node gets selected for removal
 again. Finally, note that "link2Delete" refers to the payload
 section. So, you will have to search the linked list to find
 the node to delete.
 
 
 Part 4:
 -------
 Once you have processed/recorded all of the nodes slated for
 removal, you MUST display the contents of your trash list via
 a function called:
 
 DISPLAY_TRASH(xxxx)
 
 You must then you MUST free up the trash list and display the
 remaining contents of the original list via calls to
 
 DISPLAY_INORDER(xxxx)
 DISPLAY_POSTORDER(xxxx)
 
 Finally, you must call the FREE_INORDER(xxxx) function.
 
 REQUIREMENTS:
 -------------
 1. Your program must run in Streibel 109 or on shell.aero.und.edu.
 
 2. Your full name must appear as a comment at the beginning of your
 program.
 
 3. Your source code must be named hw7-yourname.c
 
 4. Email your source (subject hw7-yourname) to rmarsh@cs.und.edu and to
 ivyjoy.serrano@my.und.edu
 
*/