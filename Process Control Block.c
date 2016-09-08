// CSci 451 HW 2
// Written May 30th, 2014
// This code written by Chris Davis
// This code implements a crude Process Control Block (PCB)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define MAX 10000

struct PCB {
	int PID; // Process ID
	double CUT; // CPU Time
	int IRT; // # of Interrupt Requests
	double WT; // Wait Time
	time_t WS; // Wait Time start
};

sem_t mutex;
sem_t work;
sem_t control;

int rRear = 0, rFront = 0, iRear = 0, iFront = 0; // Counters to keep track of the queue positions

void rDisplay(int position); // Function to display the contents of a PCB in the ready queue
void iDisplay(int position); // Function to display the contents of a PCB in the IO queue
struct PCB rDelete(); // Function to remove a PCB from the ready queue
struct PCB iDelete(); // Function to remove a PCB from the IO queue
void rInsert(int ID, double CUT, int IRT, double WT); // Function to add a PCB to the ready queue
void iInsert(int ID, double CUT, int IRT, double WT); // Function to add a PCB to the IO queue

double doWork(); // Function to simulate CPU processing. Returns a double of total time on the CPU.
void childStuff(); // Function to decide what the child process will do next

int procNum = 0; // Counter to keep track of the number of terminated processes

struct PCB ready[MAX]; // Ready Queue
struct PCB IO[MAX]; // IO queue

struct PCB PCBTemp; // Process currently in CPU

time_t start, end; // Time constructs to facilitate the passing of CPU time from the child processes.
double j; // Doesn't actually do anything, except store stuff for burning CPU cycles.

// Beginning of program
int main (void)
{
	int tPID, tCUT, tIRT, tWT; // Temp values to hold stuff which needs to be passed to the struct(s)
	
	sem_init(&mutex, 0, 0);
	sem_init(&work, 0, 0);
	sem_init(&control, 0, 0);
	
	int parent_ppid = getpid(); // Parent Process ID
	int bash_ppid = getppid();
	
	srand(time(NULL));
	tPID = fork();
	//printf("%d", tPID);
	
	//printf("\n\nPPID test: %d\n\n", getppid());
	
	if ((getppid() != parent_ppid) && (getppid() != bash_ppid)) // Child
	{
		sem_wait(&mutex);
		rInsert(getppid(), 0, 0, 0); // Add first process to ready queue
		sem_post(&mutex);	
	}
	else // Parent
	{
		// Do Nothing
	}
	//printf("Our PPID is: %d",getppid());
	//printf("our tpid is: %d",tPID);
	while (procNum < 25)
	{
		
		if ((getppid() != parent_ppid) && (getppid() != bash_ppid)) // Child
		{
			
			int temp = (rand() % 3); // Generate a random number, between 0 and 2.
			int myPID = getpid();
			double tempCounter = 0;
			
			//printf("%d\n",myPID);
			//printf("%d\n",ready[rRear].PID);
			//if (ready[rRear].PID == myPID)
			//{
				//printf("Hello\n\n\n");
				sem_wait(&control);
				childStuff(); // Process instructions for next move by child process
				sem_post(&control);
			//}
		} 
		else // Parent
		{
			//printf("%d", tPID);
			if (rFront == rRear)
			{
				tPID = fork();
				//printf("Your PID is: %d", tPID);
				if ((getppid() != parent_ppid) && (getppid() != bash_ppid)) // Child
				{
					//printf("Our PID is 0");
					sem_wait(&mutex);
					rInsert(getppid(), 0, 0, 0); // Add process to front of ready queue
					sem_post(&mutex);
				} 
				else // Parent
				{
					//printf("now: %d", tPID);
				}
			}	
			// Check Ready queue. If empty, generate a process & move it to front of ready queue
			
			// Wait for child to finish
			
			sem_post(&control);
			sem_wait(&control);
		}
		//printf("procNum: %d", procNum);
		//sleep(1);
		procNum++;
		waitpid(-1, NULL, 0);
	} // Successfully had at least 25 processes terminate
	
	return 1;
}

void rDisplay(int position) // Function to display the contents of a PCB in the ready queue
{
	printf("PID: %d\n", ready[position].PID);
	printf("CUT: %f\n", ready[position].CUT);
	printf("IRT: %d\n", ready[position].IRT);
	printf("WT: %f\n", ready[position].WT);
}

void iDisplay(int position) // Function to display the contents of a PCB in the IO queue
{
	printf("PID: %d\n", IO[position].PID);
	printf("CUT: %f\n", IO[position].CUT);
	printf("IRT: %d\n", IO[position].IRT);
	printf("WT: %f\n", IO[position].WT);
}

struct PCB rDelete() // Function to remove a PCB from the ready queue
{
	if (rFront == rRear)
	{
		printf("The ready queue is empty.\n");
	}
	else
	{
		rRear++;
	}
	return (ready[rRear-1]);
}

struct PCB iDelete() // Function to remove a PCB from the IO queue
{
	if (iFront == iRear)
	{
		printf("The IO queue is empty.\n");
	}
	else
	{
		iRear++;
	}
	return (IO[iRear-1]);
}

void rInsert(int ID, double CUT, int IRT, double WT) // Function to add a PCB to the ready queue
{
	if ((rRear == MAX) || (rFront == MAX))
	{
		printf("The ready queue is full.\n");
		return;
	}
	struct PCB temp;
	temp.PID = ID;
	//printf("our temppid: %d", temp.PID);
	temp.CUT = CUT;
	temp.IRT = IRT;
	//printf("tempirt:%f",temp.CUT);
	temp.WT = WT;
	temp.WS = time(0);
	ready[rFront] = temp;
	rFront++;
}

void iInsert(int ID, double CUT, int IRT, double WT) // Function to add a PCB to the IO queue
{
	if ((iRear == MAX) || (iFront == MAX))
	{
		printf("The IO queue is full.\n");
		return;
	}
	struct PCB temp;
	temp.PID = ID;
	temp.CUT = CUT;
	temp.IRT = IRT+1;
	
	temp.WT = WT;
	ready[iFront] = temp;
	iFront++;
}

double doWork() // Function to make simulate child process being moved to CPU
{
	sem_wait (&work);
	// Signal other processes that we are doing work
	
	start = time(0);
	// get system time
	
	for (int i = 0; i < (rand() % 100000); i++) j = sin(i);
	// do work
	
	end = time(0);
	// get system time
	
	sem_post (&work);
	// Signal other processes that we are done with the CPU
	
	double stuff = (difftime(end, start));
	
	return (stuff);
	// Return the total time on the CPU, in seconds, as a double.
}

void childStuff()
{
	int random = (rand() % 3);
	//printf("rand is: %d",random);
	if (random == 0) // Terminate process
	{
		//printf("yoooooo\n\n");
		ready[rRear].WT = (difftime(time(0),ready[rFront].WS)); // Calculate wait time (in seconds) in Ready Queue
		double temp1 = doWork();
		printf("%f",temp1);
		ready[rRear].CUT += temp1; // Do work and calculate CPU Time
		sem_wait (&mutex);
		procNum = procNum + 1;
		rDisplay(rRear);
		rDelete();
		sem_post (&mutex);
		exit(1);
		//pthread_t temp = pthread_self();
		//pthread_exit(temp);
		int tPID = getpid();
	} 
	else if (random == 1) // Return to ready queue
	{
		ready[rRear].WT = difftime(time(0),ready[rFront].WS); // Calculate wait time (in seconds) in Ready Queue
		ready[rRear].CUT += doWork(); // Do work and calculate CPU Time
		sem_wait (&mutex);
		struct PCB ret = rDelete();
		printf("PID: %d \nCUT: %f \nIRT: %d \nWT: %f\n",ret.PID, ret.CUT, ret.IRT, ret.WT);
		rInsert(ret.PID, ret.CUT, ret.IRT, ret.WT);
		sem_post (&mutex);
	}
	else if (random == 2) // Go to I/O queue
	{
		ready[rRear].WT = difftime(time(0),ready[rFront].WS); // Calculate wait time (in seconds) in Ready Queue
		ready[rRear].CUT += doWork();// Do work and calculate CPU Time
		
		sem_wait (&mutex);
		struct PCB ret = rDelete();
		iInsert(ret.PID, ret.CUT, ret.IRT, ret.WT);
		sem_post (&mutex);
		
		sleep((rand() % 60)); // Simulate making the program wait for I/O
		
		sem_wait (&mutex);
		rInsert(ret.PID, ret.CUT, ret.IRT, ret.WT);
		sem_post (&mutex);
	}
}