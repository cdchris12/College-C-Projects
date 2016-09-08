// This code created by Chris Davis
// ID Number: 0879026
// Completed on: 9/28/2014

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//sem_t mutex;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
char global[2000] = "";

void * ThreadOne(void * a)
{	
	char character[3];
    // Open file and use while loop to keep going until end of file.
	FILE *fp;
	fp = fopen("data1.txt", "r");
	if (fp == NULL) {
		printf("Can't open input file data1.txt!");
		exit(1);
	}
	
	while (fscanf(fp, "%s", character) == 1) {
		// Do file stuff here
		//sem_wait(&mutex);
		pthread_mutex_lock(&lock);
		printf("Thread 1 just locked!!!\n");
		if (strlen(global) == 0) { // First character
			strcpy(global, character);
			printf("Thread 1 just cpy'd:\t%s\n", character);
		} else if ((strlen(global) % 2) == 0){ // This insertion will be an odd number
			strcat(global, character);
			printf("Thread 1 just cat'd:\t%s\n", character);
		} else { // This insertion will be an even number, and should be populated by thread 2
			int count = 0;
			while ((strlen(global) % 2) != 0 && count < 100){
				pthread_mutex_unlock(&lock);
				printf("Thread 1 is waiting for thread 2...\n");
				pthread_mutex_lock(&lock);
				count++;
			}
			printf("Thread 1 is done waiting for thread 2...\n");
			strcat(global, character);
		}
		//sem_post(&mutex);
		//sleep(1);
		pthread_mutex_unlock(&lock);
		printf("Thread 1 just unlocked!\n");
	}
	
	fclose(fp);
	return NULL;
}

void * ThreadTwo(void * a)
{	
	char character[3];
	char temp[3];
    // Open file and use while loop to keep going until end of file.
	FILE *fp;
	fp = fopen("data2.txt", "r");
	if (fp == NULL) {
		printf("Can't open input file data2.txt!");
		exit(1);
	}
	
	while (fscanf(fp, "%s", character) == 1) {
		// Do file stuff here
		//sem_wait(&mutex);
		pthread_mutex_lock(&lock);
		//sleep(1);
		printf("Thread 2 just locked!!!\n");
		if (strlen(global) == 0) { // First char should always be populated by first thread. This loop is designed to wait indefinitely for that first char to be populated.
			while (strlen(global) == 0){
				pthread_mutex_unlock(&lock);
				printf("Thread 2 is waiting for thread 1...\n");
				pthread_mutex_lock(&lock);
			}
			printf("Thread 2 is done waiting for thread 1...\n");
			strcat(global, character);
			printf("Thread 2 just cat'd:\t%s\n", character);
		} else{ // It's my turn!
			strcat(global, character);
			printf("Thread 2 just cat'd:\t%s\n", character);
		}
		//sem_post(&mutex);
		pthread_mutex_unlock(&lock);
		printf("Thread 2 just unlocked!\n");
	}
	
	fclose(fp);
	return NULL;
}

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;
	
	//sem_init(&mutex, 0, 1);
	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("\nMutex initiation failed!\n");
		return 1;
	}

    if(pthread_create(&tid1, NULL, ThreadOne, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, ThreadTwo, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }
  
    printf("\nThe decoded message is:\n\n%s\n\n", global);
	
	pthread_mutex_destroy(&lock);
	pthread_exit(NULL);
}

// Thread psuedocode:
//		sem_wait (&mutex);
//		(Do work)
//		sem_post (&mutex);

