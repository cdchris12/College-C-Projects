// A header file for functions

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include "./hw9-chrisdavis.c"



void DisplayInorder (struct node *head1); // Prototype

void DisplayPostorder (struct node *tail1); // Prototype

void DisplayTrash (struct node *trashHead1); // Prototype

void FreeInorder (struct node *head2); // Prototype

void FreeTrash (struct node *trashHead2); // Prototype

int AddToTrash (struct node *toTrash, int trashSize1); // Prototype