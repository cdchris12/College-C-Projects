// This code written by Chris Davis

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    int  data;
    struct node *next;
};

struct node *searchList(int value, struct node *head);

int main (void)
{
    int i, search;
    struct node *current, *head, *temp;
    head = NULL;
    
    for(i = 0; i < 10; i++)
    {
        if (head == NULL)
        {
            temp = (struct node *)malloc(sizeof(struct node));
            temp->data = i;
            temp->next = NULL;
            current = temp;
            head = temp;
        }
        else
        {
            temp = (struct node *)malloc(sizeof(struct node));
            current->next = temp;
            temp->data = i;
            current = temp;
        }
    }
    current = head;
    
    while (current) {
        printf("%d\n", current->data);
        current = current->next ;
    }
    
    printf("Please select a number to search the linked list for: \n");
    scanf("%d", &search);
    printf("[%d %d]\n", search, searchList(search, head)->data);
    
    current = head;
    
    while (current)
    {
        temp = current;
        current = current->next;
        //printf("%d\n", temp->data); // For testing purposes
        free (temp);
    }
    
}

struct node *searchList(int value, struct node *head)
{
    struct node *current;
    current = head;
    while (current)
    {
        if (current->data == value)
            return(current);
        else
        {
            current = current->next;
        }
    }
}






/*HW-5	CS230	10 points	Due: June 13

Write a program that uses a pointer-based linked
list. You should use the following struct (declared
                                           as a global):

struct node {
    int  data;
    struct node *next;
};

Your program must use a for loop to count from 0
to 9. Your program must insert these into a linked
list such that they can be retrieved in low-to-high
order (note that the example in class retrieved in
       high-to-low order).

Your program must display the results using the
following code (from class) without any modifications:

while (current) {
    printf("%d\n", current->data);
    current = current->next ;
}


Next, your program must prompt the user for a value and
call a linear search function to find that value.
If the value is found, your program must print out
the value. You must use this code to print the value

printf("[%d %d]\n", search, searchList(search, head)->data);

and this prototype for the search function:

link *searchList(int value, link *head)


Your program must also correctly free all links
of the list.


REQUIREMENTS:
-------------
1. Your program must run in Streibel 109 or on shell.aero.und.edu.

2. Your full name must appear as a comment at the beginning of your
program.

3. Your source code must be named hw5-yourname.c

4. Email your source (subject hw5-yourname) to rmarsh@cs.und.edu and to
ivyjoy.serrano@my.und.edu*/