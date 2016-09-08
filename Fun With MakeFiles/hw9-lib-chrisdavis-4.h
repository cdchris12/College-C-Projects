// A header file for functions

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include "./hw9-chrisdavis.c"

struct node {
    int  data;
    struct node *next;
    struct node *prev;
};

void DisplayInorder (struct node *head1); // Prototype

void DisplayPostorder (struct node *tail1); // Prototype

void DisplayTrash (struct node *trashHead1); // Prototype

void FreeInorder (struct node *head2); // Prototype

void FreeTrash (struct node *trashHead2); // Prototype

void AddToTrash (struct node *toTrash, struct node *trashHead, int trashSize); // Prototype