// This code created by Chris Davis
// ID Number: 0879026
// Completed on: 10/26/2014

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

struct node {
    int  data;
	int  pos; // Position in the linked list
    struct node *next;
    struct node *prev;
};

struct node *current;
struct node *temp;
struct node *head = NULL;
struct node *tail;
//head = NULL;

//sem_t mutex;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * ThreadOne(void * a)
{
	//sem_wait(&mutex);
	int i = 1;
	struct node *cur;
	cur = head;
	while (1){
		/* Start Critical Section */
		pthread_mutex_lock(&lock);
		//printf("Thread 1 just locked!!!\n");
		
		//sleep(1);
		cur->data = i;
		cur = cur->next;
		i++;
		
		pthread_mutex_unlock(&lock);
		//printf("Thread 1 just unlocked!\n");
		/* End Critical Section */
	}
	
	return NULL;
}

void * ThreadTwo(void * a)
{
	//sem_wait(&mutex);
	struct node *cur;
	cur = tail;
	while (1){
		/* Start Critical Section */
		pthread_mutex_lock(&lock);
		//printf("Thread 1 just locked!!!\n");
		
		//sleep(1);
		printf("Link:  %d\tData:  %d\n", cur->pos, cur->data);
		cur = cur->prev;
		
		pthread_mutex_unlock(&lock);
		//printf("Thread 1 just unlocked!\n");
		/* End Critical Section */
	}
	return NULL;
}

int main(int argc, char * argv[])
{
	// For loop to insert data into linked list
	int i;
	for(i=1; i <= 27; i++)
	{
	    if (head == NULL)
	    {
	        if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL)
	        {
	            // haven't fixed this yet
	            temp->data = 0;
				temp->pos = i;
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
	            temp->data = 0;
				temp->pos = i;
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
	
	// Link the two ends of the list
	tail->next = head;
	head->prev = tail;
	
    pthread_t tid1, tid2;
	
	//sem_init(&mutex, 0, 1);
	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("\nMutex initiation failed!\n");
		return 1;
	}

    if(pthread_create(&tid1, NULL, ThreadOne, NULL))
    {
      printf("\n ERROR creating thread 1.\n");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, ThreadTwo, NULL))
    {
      printf("\n ERROR creating thread 2.\n");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread 1.\n");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread 2.\n");
      exit(1);
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
	
	pthread_mutex_destroy(&lock);
	pthread_exit(NULL);
}

// Thread psuedocode:
//		sem_wait (&mutex);
//		(Do work)
//		sem_post (&mutex);


/*
HW-7		CS451	10 points	Due: Monday, October 27

Write a program that creates a doubly-linked circular linked 
list of length 27. The linked list MUST be developed using 
pointers (not an array-based linked list). The data contained 
by the linked list will be a simple integer.

The program must also create 2 threads:

One thread is a producer that navigates the linked list in a 
clockwise order and that writes an integer (of increasing value 
1, 2, 3, ...N) to each link as they are encountered.

The second thread is a consumer that navigates the linked list 
in a counter-clockwise order and that reads the integer data from 
each link and that prints the link number and integer data on the 
screen. I.e.

   Link #n <tab> Data x

The problem here is that we have a data oriented critical section 
problem (not a code oriented critical section problem) and you 
must devise and implement a method to prevent any lost updates.

Notes: 
------
1) You cannot use pthread_join to artificially start and stop the 
   threads.
2) You cannot restart the threads once that have been started.
3) I don't even think you need a mutex/semaphore. There is a fairly
   simple way to manage this problem.

REQUIREMENTS:
-------------
1. Your program must run in Streibel 109/115.

2. Your full name must appear as a comment at the beginning of your 
   program.

3. Your source code must be named hw7-yourname.c or hw7-yourname.cpp

4. Email your source (subject hw7-yourname) to rmarsh@cs.und.edu*/