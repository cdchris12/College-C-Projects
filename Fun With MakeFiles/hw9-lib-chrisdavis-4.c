// This is a library of the program's functions

//#include "./hw9-lib-chrisdavis.h"
#include <stdio.h>

extern struct node {
    int  data;
    struct node *next;
    struct node *prev;
};

//extern struct node *trashTail, *trashHead, *trashCurrent;

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

void AddToTrash (struct node *toTrash, struct node *trashHead, int trashSize)
{
    printf("Nope.....\n");
    struct node *trashCurrent1;
    
    if (trashSize == 0)
    {
        printf("abcdef\n");
        trashHead = toTrash;
        trashCurrent1 = toTrash;
        toTrash->prev = NULL;
        toTrash->next = NULL;
        //trashSize1++;
    }
    else
        printf("Nope\n");
    
    /*else
    {
        // Start at the head of the linked list
        trashCurrent = trashHead;
        
        // Walk through the linked list
        while (trashCurrent->next != NULL)
        {
            trashCurrent = trashCurrent->next;
        }
        
        // Do stuff
        toTrash->next = NULL;
        trashCurrent->next = toTrash;
        toTrash->prev = trashCurrent;
        trashCurrent = trashCurrent->next;
        trashTail = trashCurrent;
        //trashSize1++;
    }*/
    
    //return *trashHead1;
    
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