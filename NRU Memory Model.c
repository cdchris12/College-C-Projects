// This code created by Chris Davis
// ID Number: 0879026
// Completed on: 10/13/2014

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int LIMIT = 50000;

//sem_t mutex;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int memory[5000][3];
// The structure of the array is: [PID], [R Bit], [M Bit]

void * ThreadOne(void * a)
{
	int PID = 100;
	//sem_wait(&mutex);
	int N = 0, j = 0, random = 0;
	while (1){
		N = rand() % 5000;
		random = rand() % 2;
	
		if ((memory[N][0] == PID) || (memory[N][0] == 0)) {
			// Either a free page or a page owned by this PID
			if (random == 0){
				// Set PID & R bit
				/* Start Critical Section */
				pthread_mutex_lock(&lock);
				//printf("Thread 1 just locked!!!\n");
				//sem_post(&mutex);
				//sleep(1);
				memory[N][0] = PID;
				memory[N][1] = 1;
				pthread_mutex_unlock(&lock);
				//printf("Thread 1 just unlocked!\n");
				/* End Critical Section */
			
			} else if (random == 1){
				// Set PID & R & M bits
				/* Start Critical Section */
				pthread_mutex_lock(&lock);
				//printf("Thread 1 just locked!!!\n");
				//sem_post(&mutex);
				//sleep(1);
				memory[N][0] = PID;
				memory[N][1] = 1;
				memory[N][2] = 1;	
				pthread_mutex_unlock(&lock);
				//printf("Thread 1 just unlocked!\n");
				/* End Critical Section */
			}
		} else {
			// Page owned by someone else
			printf("Page Fault!\nN:%d\tR:%d\tM:%d\n", N, memory[N][1], memory[N][2]);
		}
		j++;
	}
	
	return NULL;
}

void * ThreadTwo(void * a)
{
	int PID = 200;
	//sem_wait(&mutex);
	int N = 0, j = 0, random = 0;
	while (1){
		N = rand() % 5000;
		random = rand() % 2;
	
		if ((memory[N][0] == PID) || (memory[N][0] == 0)) {
			// Either a free page or a page owned by this PID
			if (random == 0){
				// Set PID & R bit
				/* Start Critical Section */
				pthread_mutex_lock(&lock);
				//printf("Thread 2 just locked!!!\n");
				//sem_post(&mutex);
				//sleep(1);
				memory[N][0] = PID;
				memory[N][1] = 1;
				pthread_mutex_unlock(&lock);
				//printf("Thread 2 just unlocked!\n");
				/* End Critical Section */
			
			} else if (random == 1){
				// Set PID & R & M bits
				/* Start Critical Section */
				pthread_mutex_lock(&lock);
				//printf("Thread 2 just locked!!!\n");
				//sem_post(&mutex);
				//sleep(1);
				memory[N][0] = PID;
				memory[N][1] = 1;
				memory[N][2] = 1;	
				pthread_mutex_unlock(&lock);
				//printf("Thread 2 just unlocked!\n");
				/* End Critical Section */
			}
		} else {
			// Page owned by someone else
			printf("Page Fault!\nN:%d\tR:%d\tM:%d\n", N, memory[N][1], memory[N][2]);
		}
		j++;
	}
	return NULL;
}

void * ThreadThree(void * a)
{
	int PID = 300;
	//sem_wait(&mutex);
	int N = 0, j = 0, random = 0;
	while (1){
		N = rand() % 5000;
		random = rand() % 2;
	
		if ((memory[N][0] == PID) || (memory[N][0] == 0)) {
			// Either a free page or a page owned by this PID
			if (random == 0){
				// Set PID & R bit
				/* Start Critical Section */
				pthread_mutex_lock(&lock);
				//printf("Thread 3 just locked!!!\n");
				//sem_post(&mutex);
				//sleep(1);
				memory[N][0] = PID;
				memory[N][1] = 1;
				pthread_mutex_unlock(&lock);
				//printf("Thread 3 just unlocked!\n");
				/* End Critical Section */
			
			} else if (random == 1){
				// Set PID & R & M bits
				/* Start Critical Section */
				pthread_mutex_lock(&lock);
				//printf("Thread 3 just locked!!!\n");
				//sem_post(&mutex);
				//sleep(1);
				memory[N][0] = PID;
				memory[N][1] = 1;
				memory[N][2] = 1;	
				pthread_mutex_unlock(&lock);
				//printf("Thread 3 just unlocked!\n");
				/* End Critical Section */
			}
		} else {
			// Page owned by someone else
			printf("Page Fault!\nN:%d\tR:%d\tM:%d\n", N, memory[N][1], memory[N][2]);
		}
		j++;
	}
	return NULL;
}

void * ThreadFour(void * a)
{
	struct timespec t;
	t.tv_sec = 0;
	t.tv_nsec = 500000000; // Five hundred million nanoseconds is half a second.
	//sem_wait(&mutex);
	while (1){
		int i = 0, c2 = 0, c3 = 0;
		int flag = 0;
		for (i=0; i++; i<LIMIT){
			if (memory[i][0] != 0){
				// Page is owned by SOMEONE
				if ((memory[i][1] == 1) && (memory[i][2] == 1)){
					// Class 3 page
					if (c3 == 0){
						c3 = i;
					}
				} else if ((memory[i][1] == 1) && (memory[i][2] == 0)){
					// Class 2 page
					if (c2 == 0){
						c2 = i;
					}
				} else if ((memory[i][1] == 0) && (memory[i][2] == 1)){
					// Class 1 page
					c2 = 0;
					c3 = 0;
					
					/* Start Critical Section */
					pthread_mutex_lock(&lock);
					//printf("Thread 4 just locked!!!\n");
					//sem_post(&mutex);
					//sleep(1);
					memory[i][0] = 0;
					memory[i][2] = 0;
					pthread_mutex_unlock(&lock);
					//printf("Thread 4 just unlocked!\n");
					/* End Critical Section */
					
					nanosleep(&t, NULL);
					break;
				}
			} else {
				// Class 0 page
				continue;
			}
		}
		if (c2 != 0){
			c3 = 0;
			/* Start Critical Section */
			pthread_mutex_lock(&lock);
			//printf("Thread 4 just locked!!!\n");
			//sem_post(&mutex);
			//sleep(1);
			memory[c2][0] = 0;
			memory[c2][1] = 0;
			pthread_mutex_unlock(&lock);
			//printf("Thread 4 just unlocked!\n");
			/* End Critical Section */
			
			c2 = 0;
		} else if ((c3 != 0) && (c2 == 0)) {
			c2 = 0;
			
			/* Start Critical Section */
			pthread_mutex_lock(&lock);
			//printf("Thread 4 just locked!!!\n");
			//sem_post(&mutex);
			//sleep(1);
			memory[c3][0] = 0;
			memory[c3][1] = 0;
			memory[c3][2] = 0;
			pthread_mutex_unlock(&lock);
			//printf("Thread 4 just unlocked!\n");
			/* End Critical Section */
			
			nanosleep(&t, NULL);
		}
	}
	return NULL;
}

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2, tid3, tid4;
	
	unsigned int seed = 1492;
	srand(seed);
	int q = 0;
	for (q; q++; q<5000){
		memory[q][0] = 0;
		memory[q][1] = 0;
		memory[q][2] = 0;
	} // Initalize all values to 0 for comparison purposes
	
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
	
    if(pthread_create(&tid3, NULL, ThreadThree, NULL))
    {
      printf("\n ERROR creating thread 3.\n");
      exit(1);
    }

    if(pthread_create(&tid4, NULL, ThreadFour, NULL))
    {
      printf("\n ERROR creating thread 4.\n");
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
	
    if(pthread_join(tid3, NULL))	/* wait for the thread 3 to finish */
    {
      printf("\n ERROR joining thread 3.\n");
      exit(1);
    }

    if(pthread_join(tid4, NULL))        /* wait for the thread 4 to finish */
    {
      printf("\n ERROR joining thread 4.\n");
      exit(1);
    }
	
	pthread_mutex_destroy(&lock);
	pthread_exit(NULL);
}

// Thread psuedocode:
//		sem_wait (&mutex);
//		(Do work)
//		sem_post (&mutex);


/*
HW-5    CS451   10 points       Due: Monday, October 13, 2014

PART 1.
-------
Write a program that uses 4 threads to manipulate the memory
space using a NRU model.

1. Create a simmulated memory space for 5000 pages. The memory
must contain the modifying process ID, the R bit, and the M bit.
(I suggest using a 3 column array to hold the required data).  

2. Three threads (e.g. PID 100, 200 and 300) will each continuously 
randomly generate a value between 0 and 4999 and a random value of 
0 or 1. The first random value generated will indicate what page to 
manipulate. The second random value generated will indicate what to 
do to that page:
    0 - means you read from it (set R bit).
    1 - means you write to it (set R and M bits).

3. Obviously, Whenever a thread randomly requests a page, if the 
page is not claimed by someone else you can simply mark the fields 
as required. However, if the page is claimed by someone else print 
out the text "Page fault: N R M" (where N is tha page number and R/M 
are the R & M bits) and move on (ignore this attempt and look for a 
new random page).

If no PID, put in PID

4. The fourth thread will act as a garbage collector. It will continually
scan the memory space looking for the first instance of the lowest class 
memory (see class notes). If the page has the R bit set, the thread can 
simply reset the R bit to 0. If the page has the M bit set, the thread must
reset the M bit to 0 and delay/sleep for 0.5 second.

When 

Find earliest instance of lowest class of memory and work on it.
3 - PID set, R & M bit set to 1
2 - PID set, R bit set to 1, M bit set to 0
1 - PID set, R bit set to 0, M bit set to 1
0 - PID not set, no R or M bit

5. This may seem like an easy assignment, but you must recognize that the
fourth thread will occasionally conflict with the other 3 threads (will 
try to access an array element at the same time). Thus, you ***MUST*** 
include a mutex(s) to synchronize these threads. 

Only one mutex for all proccesses, sleep outside the mutex

6. Finally, to ensure that everone's code runs the same, you MUST seed
the random number generator with the value 1492. Because that is when 
"Columbus sailed the ocean blue."

REQUIREMENTS:
------------
1. Your program must run in Streibel 109/115.

2. Your full name must appear as a comment at the beginning of your 
   program.

3. Your source code must be named hw5-yourname.c or hw5-yourname.cpp

4. Email your source (subject hw5-yourname) to rmarsh@cs.und.edu 
*/
