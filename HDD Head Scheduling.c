// This code created by Chris Davis
// ID Number: 0879026
// Completed on: 11/19/2014

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct queue {
    struct node *top;
    struct node *bottom;
    struct node *current;
    int length;
};

struct queue *job_queue = NULL;
struct queue *q_temp = NULL;
struct queue *temp_queue = NULL;
struct node *temp = NULL;

volatile sig_atomic_t time_limit = false;
int counter = 0;
bool NStep = false;
bool SCAN = false;
int N = 15;

void handle_alarm( int sig ) {
    time_limit = true;
}


//sem_t mutex;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * ThreadOne(void * a) {    
    srand(1492);
    int random_num = 0;
    
    // <---- Queue Setup ---->
    if ((q_temp = (struct queue *)malloc(sizeof(struct queue))) == NULL) { // Instiantiate a new queue
        printf("Memory allocation failed for the job_queue!!\n");
        exit(0);
    } else {
        job_queue = q_temp;
        job_queue->top = NULL;
        job_queue->bottom = NULL;
        job_queue->current = NULL;
        job_queue->length = 0;
        printf("Thread 1 setup the job_queue!!\n");
    }
    if (NStep){ // We only need the temp queue if we're using Nstep
        if ((q_temp = (struct queue *)malloc(sizeof(struct queue))) == NULL) { // Instiantiate a new queue
            printf("Memory allocation failed for the temp_queue!!\n");
            exit(0);
        } else {
            temp_queue = q_temp;
            temp_queue->top = NULL;
            temp_queue->bottom = NULL;
            temp_queue->current = NULL;
            temp_queue->length = 0;
            printf("Thread 1 setup the temp_queue!!\n");
        }
    }
    // <---- Queue Setup ---->
    
    int z = 0;
    
    // <---- Populate Queue With Data ---->
    while (time_limit != true) {
        usleep(100000);
        /* Start Critical Section */
		pthread_mutex_lock(&lock);
		printf("Thread 1 just locked!!!\n");
               
        if (SCAN){
            //TODO: Write an insertion sort algorithm for the job_queue, so that requests are always sorted from smallest position (bottom) to largest position (top).
            random_num = (rand()%1000) + 1;
            printf("Thread 1, pass %d:\n", z);
            z++;
            
    	    if (job_queue->top == NULL) { // Nothing on the job queue, need to create the first node.
    	        if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL) { // Instantiate a new node
    				temp->data = random_num;
    	            temp->next = NULL;
    	            temp->prev = NULL;
    	            job_queue->top = temp;
    	            job_queue->bottom = temp;
                    job_queue->current = temp;
                    job_queue->length++;
                    printf("Thread one created the first node!!\n");
    	        } else {
    	            printf("Memory allocation failed for a node!!\n");
                    exit(0);
                }
    	    } else { // Queue not empty, need to do something with it.
                job_queue->current = job_queue->top;
                while (job_queue->current != NULL) { // Iterate through the queue, starting at the top (biggest #), and moving towards the bottom (smallest #)
                    if (random_num < job_queue->current->data) { // If random is less than this node's data, go to next node in queue
                        if (job_queue->current->prev != NULL) { // There is a next node; switch the current pointer to it.
                            job_queue->current = job_queue->current->prev;
                        } else { // There is no next node; add this node here and update the bottom pointer.
                	        if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL) { // instantiate a new node
                                temp->data = random_num;
                	            temp->next = job_queue->current;
                	            temp->prev = NULL;
                                job_queue->current->prev = temp;
                                job_queue->bottom = temp;
                                job_queue->length++;
                                printf("Thread one created an additional node (1)!!\n");
                                break;
                	        } else {
                	            printf("Memory allocation failed for a node!!\n");
                                exit(0);
                            }
                        }
                    } else { // Random is equal to or greater than the current node, but less than the next node (remember we're working backwards); create a node and insert it into the list here
                        if (job_queue->current->next == NULL) { // We're at the top of the queue; this is a special case we'll need to cover.
                	        if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL) { // instantiate a new node
                                temp->data = random_num;
                	            temp->next = NULL;
                	            temp->prev = job_queue->current;
                                job_queue->current->next = temp;
                                job_queue->top = temp;
                                job_queue->length++;
                                printf("Thread one created an additional node (2)!!\n");
                                break;
                	        } else {
                	            printf("Memory allocation failed for a node!!\n");
                                exit(0);
                            }
                        } else { // We're not at either end of the queue
                	        if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL) { // instantiate a new node
                                temp->data = random_num;
                	            temp->next = job_queue->current->next;
                	            temp->prev = job_queue->current;
                                job_queue->current->next->prev = temp;
                                job_queue->current->next = temp;
                                job_queue->length++;
                                printf("Thread one created an additional node (3)!!\n");
                                break;
                	        } else {
                	            printf("Memory allocation failed for a node!!\n");
                                exit(0);
                            }
                        }
                    }
                }
                job_queue->current = job_queue->top;
            }
        } else if (NStep){ // Don't sort the queue, just keep adding to the top of it.
    	    if (job_queue->top == NULL) { // First node
    	        if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL) { // Instantiate a new node
    				temp->data = (rand()%1000) + 1;
    	            temp->next = NULL;
    	            temp->prev = NULL;
    	            job_queue->top = temp;
    	            job_queue->bottom = temp;
                    job_queue->current = temp;
                    job_queue->length++;
                    printf("Thread one created the first node!!\n");
    	        } else {
    	            printf("Memory allocation failed for a node!!\n");
                    exit(0);
                }
    	    } else { // Adding a new node to the top of the queue.
    	        if ((temp = (struct node *)malloc(sizeof(struct node))) != NULL) { // instantiate a new node
                    temp->data = (rand()%1000) + 1;
    	            temp->next = NULL;
    	            temp->prev = job_queue->current;
                    job_queue->current->next = temp;
    	            job_queue->top = temp;
                    job_queue->current = temp;
                    job_queue->length++;
                    printf("Thread one created an additional node (4)!!\n");
    	        } else {
    	            printf("Memory allocation failed for a node!!\n");
                    exit(0);
                }
    	    }
        }
        
		pthread_mutex_unlock(&lock);
		printf("Thread 1 just unlocked!\n");
		/* End Critical Section */
	}
    // <---- Populate Queue With Data ---->
    
    return NULL;
}


void * ThreadTwo(void * a) {
    //TODO: Add some stuff here
    
    struct node *pointer = NULL;
    struct node *garbage = NULL;
    int previous_num;
    int j;
    int diff;
    int y = 0;
    
    printf("Thread 2 is waiting for the queue to fill...\n");
    while (job_queue == NULL) { // Ensure that the queue(s) are instantiated before we start working on them
        usleep(50);
    }
    printf("Thread 2 is done waiting for the queue to fill!!\n");
    
    printf("Thread 2 saw a valid job_queue!!\n");
    
    while (time_limit != true) {
        usleep(500000);
        printf("Thread 2 woke up!!\n");
        printf("Thread 2 pass %d:\n", y);
        y++;
        if (SCAN) {
            previous_num = 1; // Start the reading at the inside track (smallest number)
            pointer = job_queue->bottom; // Instiantiate a pointer to the bottom of the queue
            while (pointer != NULL && time_limit != true) { // Walk through the queue from bottom to top
                //usleep(50000);
                diff = pointer->data - previous_num; // Calculate the distance (value to usleep for)
                printf("Thread 2 is sleeping for\t\t%d milliseconds!! (1)\n", diff);
                diff = diff * 1000; // Convert from microseconds to milliseconds
                previous_num = pointer->data; // Update current read location
                usleep(diff); // Simulate moving from point to point on the HDD
                counter++; // Increment the counter.
                
        		/* Start Critical Section */
        		pthread_mutex_lock(&lock);
        		printf("Thread 2 just locked!!!\n");
                
                if (pointer->prev == NULL) { // At the bottom of the list
                    pointer = pointer->next;
                    free(pointer->prev); // Free the node we just processed
                    job_queue->length--; // Update the length of the queue
                    pointer->prev = NULL;
                    job_queue->bottom = pointer;
                } else if (pointer->next == NULL) { // At the top of the list
                    pointer = pointer->prev;
                    free(pointer->next); // Free the node we just processed
                    job_queue->length--; // Update the length of the queue
                    pointer->next = NULL;
                    job_queue->top = pointer;
                    pointer = NULL;
                } else { // In the middle of the list somewhere
                    garbage = pointer;
                    pointer = pointer->next;
                    garbage->prev->next = pointer;
                    pointer->prev = garbage->prev;
                    free(garbage);// Free the node we just processed
                    job_queue->length--; // Update the length of the queue
                }
                
        		pthread_mutex_unlock(&lock);
        		printf("Thread 2 just unlocked!\n");
        		/* End Critical Section */
            }
            
            previous_num = 1000; // Start the reading at the outside track (largest number)
            pointer = job_queue->top; // Instiantiate a pointer to the top of the queue
            
            while (pointer != NULL && time_limit != true) { // Walk through the queue from top to bottom
                //usleep(50000);
                diff = previous_num - pointer->data; // Calculate the distance (value to usleep for)
                printf("Thread 2 is sleeping for\t\t%d milliseconds!! (2)\n", diff);
                diff = diff * 1000; // Convert from microseconds to milliseconds
                previous_num = pointer->data; // Update current read location
                usleep(diff); // Simulate moving from point to point on the HDD
                counter++; // Increment the counter.
                
        		/* Start Critical Section */
        		pthread_mutex_lock(&lock);
        		printf("Thread 2 just locked!!!\n");
                
                if (pointer->prev == NULL) { // At the bottom of the list
                    pointer = pointer->next;
                    free(pointer->prev); // Free the node we just processed
                    job_queue->length--; // Update the length of the queue
                    pointer->prev = NULL;
                    job_queue->bottom = pointer;
                    pointer = NULL;
                } else if (pointer->next == NULL) { // At the top of the list
                    pointer = pointer->prev;
                    free(pointer->next); // Free the node we just processed
                    job_queue->length--; // Update the length of the queue
                    pointer->next = NULL;
                    job_queue->top = pointer;
                } else { // In the middle of the list somewhere
                    garbage = pointer;
                    pointer = pointer->prev;
                    garbage->next->prev = pointer;
                    pointer->next = garbage->next;
                    free(garbage);// Free the node we just processed
                    job_queue->length--; // Update the length of the queue
                }
                
        		pthread_mutex_unlock(&lock);
        		printf("Thread 2 just unlocked!\n");
        		/* End Critical Section */
            }
        } else if (NStep && job_queue->length > 15 && time_limit != true) {
            // <---- Grab A Subqueue ---->
    		/* Start Critical Section */
    		pthread_mutex_lock(&lock);
    		printf("Thread 2 just locked!!!\n");
            
            for (j = 0; j < N && time_limit != true; j++) { // Move the pointer forward through N nodes
                pointer = job_queue->bottom;
                
                if (j ==0){ // Just add the first node to the temp queue with no sorting at all.
                    job_queue->bottom = job_queue->bottom->next;
                    job_queue->bottom->prev = NULL;
                    
                    temp_queue->bottom = pointer;
                    temp_queue->top = pointer;
                    temp_queue->current = pointer;
                    pointer->next = NULL;
                    pointer->prev = NULL;
                    
                    temp_queue->length++;
                    job_queue->length--;
                    printf("Thread 2 just added the first node to the temp_queue!!\n");
        	    } else { // Temp_queue not empty, need to do something with this additional node.
                    temp_queue->current = temp_queue->top;
                    while (temp_queue->current != NULL) { // Iterate through the queue, starting at the top (biggest #), and moving towards the bottom (smallest #)
                        if (pointer->data < temp_queue->current->data) { // If new node's data is less than this node's data, go to next node in queue
                            if (temp_queue->current->prev != NULL) { // There is a next node; switch the current pointer to it.
                                temp_queue->current = temp_queue->current->prev;
                            } else { // There is no next node; add this node here and update the bottom pointer.
                                job_queue->bottom = job_queue->bottom->next;
                                job_queue->bottom->prev = NULL;
                                
                                temp_queue->bottom->prev = pointer;
                                pointer->next = temp_queue->bottom;
                                temp_queue->bottom = pointer;
                                temp_queue->bottom->prev = NULL;
                                
                                temp_queue->length++;
                                job_queue->length--;
                                printf("Thread 2 just added a node to the bottom of the temp_queue!!\n");
                                break;
                            }
                        } else { // Random is equal to or greater than the current node, but less than the next node (remember we're working backwards); create a node and insert it into the list here
                            if (temp_queue->current->next == NULL) { // We're at the top of the queue; this is a special case we'll need to cover.
                                job_queue->bottom = job_queue->bottom->next;
                                job_queue->bottom->prev = NULL;
                                
                                temp_queue->top->next = pointer;
                                pointer->prev = temp_queue->top;
                                temp_queue->top = pointer;
                                temp_queue->top->next = NULL;
                                
                                temp_queue->length++;
                                job_queue->length--;
                                printf("Thread 2 just added a node to the top of the temp_queue!!\n");
                                break;
                            } else { // We're not at either end of the queue
                                job_queue->bottom = job_queue->bottom->next;
                                job_queue->bottom->prev = NULL;
                            
                                temp_queue->current->next->prev = pointer;
                                pointer->next = temp_queue->current->next;
                                pointer->prev = temp_queue->current;
                                temp_queue->current->next = pointer;
                            
                                temp_queue->length++;
                                job_queue->length--;
                                printf("Thread 2 just added a node to the middle of the temp_queue!!\n");
                                break;
                            }
                        }
                    }
                    temp_queue->current = temp_queue->top;
                }
            }
    		pthread_mutex_unlock(&lock);
    		printf("Thread 2 just unlocked (1)!\n");
    		/* End Critical Section */
            // <---- Grab A Subqueue ---->
            
            pointer = temp_queue->bottom; // Instiantiate a pointer to the bottom of the queue
            previous_num = 1; // Start the reading at the inside track (smallest number)
            while (pointer != NULL && time_limit != true && temp_queue->length >= 1) { // Walk through the queue from bottom to top
                
                diff = pointer->data - previous_num; // Calculate the distance (value to usleep for)
                printf("Thread 2 is sleeping for\t\t%d milliseconds!! (3)\n", diff);
                diff = diff * 1000; // Convert from microseconds to milliseconds
                previous_num = pointer->data; // Update current read location
                usleep(diff); // Simulate moving from point to point on the HDD
                counter++; // Increment the counter.
                
                if (pointer->next == NULL && pointer->prev == NULL) { // Last node in the list
                    //printf("The current value of pointer is (2): %p\n", pointer);
                    free(pointer); // Free the node we just processed
                    temp_queue->length--; // Update the length of the queue
                    pointer->next = NULL;
                    temp_queue->top = NULL;
                    temp_queue->current = NULL;
                    temp_queue->bottom = NULL;
                    pointer = NULL;
                    printf("Thread 2 just processed the last node in temp_queue!!\n");
                } else if (pointer->next == NULL) { // At the top of the list
                    //printf("The current value of pointer is: %p\n", pointer);
                    pointer = pointer->prev;
                    free(pointer->next); // Free the node we just processed
                    temp_queue->length--; // Update the length of the queue
                    pointer->next = NULL;
                    temp_queue->top = pointer;
                    pointer = NULL;
                    printf("Thread 2 just processed the top node in temp_queue!!\n");
                } else if (pointer->prev == NULL) { // At the bottom of the list
                    //printf("The current value of pointer->next is: %p\n", pointer->next);
                    pointer = pointer->next;
                    free(pointer->prev); // Free the node we just processed
                    temp_queue->length--; // Update the length of the queue
                    pointer->prev = NULL;
                    temp_queue->bottom = pointer;
                    printf("Thread 2 just processed the bottom node in temp_queue!!\n");
                } else { // In the middle of the list somewhere
                    //printf("The current value of pointer->prev is: %p\n", pointer->prev);
                    garbage = pointer;
                    pointer = pointer->next;
                    garbage->prev->next = pointer;
                    pointer->prev = garbage->prev;
                    free(garbage);// Free the node we just processed
                    temp_queue->length--; // Update the length of the queue
                    printf("Thread 2 just processed a middle node in temp_queue!!\n");
                }
            }
            
            printf("Thread 2 is waiting for the queue to fill...\n");
            while (job_queue->length <= 15) { // Ensure that the queue(s) are instantiated before we start working on them
                usleep(50);
            }
            printf("Thread 2 is done waiting for the queue to fill!!\n");
            
            // <---- Grab A Subqueue ---->
    		/* Start Critical Section */
    		pthread_mutex_lock(&lock);
    		printf("Thread 2 just locked!!!\n");
            
            for (j = 0; j < N && time_limit != true; j++) { // Move the pointer forward through N nodes
                pointer = job_queue->bottom;
                
                if (j ==0){ // Just add the first node to the temp queue with no sorting at all.
                    job_queue->bottom = job_queue->bottom->next;
                    job_queue->bottom->prev = NULL;
                    
                    temp_queue->bottom = pointer;
                    temp_queue->top = pointer;
                    temp_queue->current = pointer;
                    pointer->next = NULL;
                    pointer->prev = NULL;
                    
                    temp_queue->length++;
                    job_queue->length--;
                    printf("Thread 2 just added the first node to the temp_queue!!\n");
        	    } else { // Temp_queue not empty, need to do something with this additional node.
                    temp_queue->current = temp_queue->top;
                    while (temp_queue->current != NULL && time_limit != true) { // Iterate through the queue, starting at the top (biggest #), and moving towards the bottom (smallest #)
                        if (pointer->data < temp_queue->current->data) { // If new node's data is less than this node's data, go to next node in queue
                            if (temp_queue->current->prev != NULL) { // There is a next node; switch the current pointer to it.
                                temp_queue->current = temp_queue->current->prev;
                            } else { // There is no next node; add this node here and update the bottom pointer.
                                job_queue->bottom = job_queue->bottom->next;
                                job_queue->bottom->prev = NULL;
                                
                                temp_queue->bottom->prev = pointer;
                                pointer->next = temp_queue->bottom;
                                temp_queue->bottom = pointer;
                                temp_queue->bottom->prev = NULL;
                                
                                temp_queue->length++;
                                job_queue->length--;
                                printf("Thread 2 just added a node to the bottom of the temp_queue!!\n");
                                break;
                            }
                        } else { // Random is equal to or greater than the current node, but less than the next node (remember we're working backwards); create a node and insert it into the list here
                            if (temp_queue->current->next == NULL) { // We're at the top of the queue; this is a special case we'll need to cover.
                                job_queue->bottom = job_queue->bottom->next;
                                job_queue->bottom->prev = NULL;
                                
                                temp_queue->top->next = pointer;
                                pointer->prev = temp_queue->top;
                                temp_queue->top = pointer;
                                temp_queue->top->next = NULL;
                                
                                temp_queue->length++;
                                job_queue->length--;
                                printf("Thread 2 just added a node to the top of the temp_queue!!\n");
                                break;
                            } else { // We're not at either end of the queue
                                job_queue->bottom = job_queue->bottom->next;
                                job_queue->bottom->prev = NULL;
                            
                                temp_queue->current->next->prev = pointer;
                                pointer->next = temp_queue->current->next;
                                pointer->prev = temp_queue->current;
                                temp_queue->current->next = pointer;
                            
                                temp_queue->length++;
                                job_queue->length--;
                                printf("Thread 2 just added a node to the middle of the temp_queue!!\n");
                                break;
                            }
                        }
                    }
                }
            }
            pthread_mutex_unlock(&lock);
    		printf("Thread 2 just unlocked! (2)\n");
    		/* End Critical Section */
            // <---- Grab A Subqueue ---->
            
            previous_num = 1000; // Start the reading at the outside track (largest number)
            pointer = temp_queue->top; // Instiantiate a pointer to the top of the queue
            
            while (pointer != NULL && time_limit != true && temp_queue->length >= 1) { // Walk through the queue from top to bottom
                diff = previous_num - pointer->data; // Calculate the distance (value to usleep for)
                printf("Thread 2 is sleeping for\t\t%d milliseconds!! (4)\n", diff);
                diff = diff * 1000; // Convert from microseconds to milliseconds
                previous_num = pointer->data; // Update current read location
                usleep(diff); // Simulate moving from point to point on the HDD
                counter++; // Increment the counter.
                
                if (pointer->next == NULL && pointer->prev == NULL) { // Last node in the list
                    free(pointer); // Free the node we just processed
                    temp_queue->length--; // Update the length of the queue
                    pointer->next = NULL;
                    temp_queue->top = NULL;
                    temp_queue->current = NULL;
                    temp_queue->bottom = NULL;
                    pointer = NULL;
                    printf("Thread 2 just processed the last node in temp_queue!!\n");
                } else if (pointer->prev == NULL) { // At the bottom of the list
                    pointer = pointer->next;
                    free(pointer->prev); // Free the node we just processed
                    temp_queue->length--; // Update the length of the queue
                    pointer->prev = NULL;
                    temp_queue->bottom = pointer;
                    pointer = NULL;
                    printf("Thread 2 just processed the bottom node in temp_queue!!\n");
                } else if (pointer->next == NULL) { // At the top of the list
                    pointer = pointer->prev;
                    free(pointer->next); // Free the node we just processed
                    temp_queue->length--; // Update the length of the queue
                    pointer->next = NULL;
                    temp_queue->top = pointer;
                    printf("Thread 2 just processed the top node in temp_queue!!\n");
                } else { // In the middle of the list somewhere
                    garbage = pointer;
                    pointer = pointer->prev;
                    garbage->next->prev = pointer;
                    pointer->next = garbage->next;
                    free(garbage);// Free the node we just processed
                    temp_queue->length--; // Update the length of the queue
                    printf("Thread 2 just processed a middle node in temp_queue!!\n");
                }
            }
        }
    }
    return NULL;
}


int main(int argc, char * argv[])
{   
    // <---- Args Checking ---->
    
    char str1[15];
    char str2[15];
    
    strcpy(str1, "SCAN");
    strcpy(str2, "N-STEP-SCAN");
    
    if (argc == 1){
        printf("You didn't enter any args. This program requires exactly (1) arg.\n");
        exit(0);
    } else if (argc == 2){
        if (strcmp(str1, argv[1]) == 0){
            SCAN = true;
        } else if (strcmp(str2, argv[1]) == 0){
            NStep = true;
        } else {
            printf("You entered an invalid selection. Please enter either '%s' or '%s'.\n", str1, str2);
            exit(0);
        }
    } else {
        printf("You entered %d args. This program requires exactly (1) arg.\n", argc);
        exit(0);
    }
    // <---- Args Checking ---->
    
    // <---- Runtime Monitoring Setup ---->
    int runtime = 60 * 5; // Make a variable to hold the number of seconds to run for (5 minutes)
    printf("This program will run for %d seconds (that's %d minute(s), just fyi).\n", runtime, runtime/60);
    signal( SIGALRM, handle_alarm ); // Install alarm handler
    alarm(runtime); // Set the alarm
    // <---- Runtime Monitoring Setup ---->
	
    // <---- Create & Start Threads ---->
    pthread_t tid1, tid2;

    if(pthread_create(&tid1, NULL, ThreadOne, NULL)) { // Create first thread
      printf("\n ERROR creating thread 1!!\n");
      exit(0);
    }
    if(pthread_create(&tid2, NULL, ThreadTwo, NULL)) { // Create second thread
      printf("\n ERROR creating thread 2!!\n");
      exit(0);
    }
    // <---- Create & Start Threads ---->
    
    int one_sec = 1;
    while (time_limit != true){ // Make the main program wait until the 5 minutes are up
        wait(&one_sec);
    }

    if(pthread_join(tid1, NULL)) {	/* wait for the thread 1 to finish */
      printf("\n ERROR joining thread 1!!\n");
      exit(0);
    }
    if(pthread_join(tid2, NULL)) {  /* wait for the thread 2 to finish */
      printf("\n ERROR joining thread 2!!\n");
      exit(0);
    }
    
    printf("\n\nTime limit expired!! Posting results...\n");
    
    if (NStep){
        printf("\nN-STEP-SCAN:\t%d drive requests serviced.\n", counter);
    } else if (SCAN) {
        printf("\nSCAN:\t%d drive requests serviced.\n", counter);
    }
    
    printf("Freeing all allocated memory...\n");
	
	// Free the array(s)
    
    while (job_queue->bottom) {
        if (!job_queue->bottom->next) {
            free(job_queue->bottom);
            break;
        }
        job_queue->bottom = job_queue->bottom->next;
        free(job_queue->bottom->prev);
    }
    
    if (NStep) {
        while(temp_queue->bottom) {
            if(!temp_queue->bottom->next){
                free(temp_queue->bottom);
                break;
            }
            temp_queue->bottom = temp_queue->bottom->next;
            free(temp_queue->bottom->prev);
        }
    }
    
    free(job_queue);
    free(temp_queue);
	
	pthread_mutex_destroy(&lock);
    
    printf("Memory freed!! Exiting...\n");
}

// Thread psuedocode:
//		sem_wait (&mutex);
//		(Do work)
//		sem_post (&mutex);


/*
HW-9	CS451	10 points	Due: Wednesday, Nov. 19

Write a program that simulates both the SCAN and the 
N-STEP-SCAN head schedulers. The choice as to whether 
the simulation is SCAN or N-STEP-SCAN must be determined 
by a command-line argument. The argument will be SCAN or 
N-STEP-SCAN. 

For either method, your program will spawn a thread that 
continuously generates a random list of head locations 
(1-1000). Make sure you seed your random number generator 
with the same seed everytime.

Your program will spawn a second thread that does the head 
scheduling simulation. To simulate the cost of the hard-drive 
mechanicals, use usleep (the value will be the distance 
from the current location/random-value to the next location
/random-value). You will also have to account for the time 
it takes the head to return to the outer region (whatever 
track is required) for the N-STEP-SCAN method.

You will also need to implement a counter to determine the 
run-time of your program. Let your program run for 5 minutes 
and then display the number of drive requests that were 
serviced. Display as follows:

SCAN:<tab>2014 drive requests serviced

Or

N-STEP-SCAN:<tab>1492 drive requests serviced


Note that you might need a mutex to synchronize the two threads.


REQUIREMENTS:
-------------
1. Your program must run on shell, room 115 or 109.

2. Your full name must appear as a comment at the beginning of your 
   program.

3. Your source code must be named hw9-yourname.c or hw9-yourname.cpp

4. Email your source (subject hw9-yourname) to rmarsh@cs.und.edu
*/