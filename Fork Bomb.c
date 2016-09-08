// CSci 451 HW 3
// Written by Chris Davis
// ID#: 0879026

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	pid_t pID = NULL;
	
	if (argc == 1) {
		printf("No arguments were passed!\n");
		exit(-1);
	} else if (argc > 2) {
		printf("Too many arguments were passed!\n");
		exit(-2);
	} else {
		// There are exactly (2) args,
		// argv[0] is the command used to call this program
		// argv[1] is the program we want to call
		//printf("argv[1]: %s\nargv[2]: %s\n", argv[0], argv[1]);
		pID = fork();
		if (pID == 0) { // This is the child
			execlp(argv[1], argv[1], (char *) 0);
			// Run the graphical program
		} else if (pID < 0) { // Failed to fork
			printf("I failed to fork!");
			exit(-3);
		} else { // This is the parent
			execl(argv[0], argv[0], argv[1], (char *) 0);
			// Reload this program from memory
		}
	}
}

/*
HW-3	CS451	10 points	Due: Friday, September 19

***********************************************************************
* DO NOT RUN THIS ON SHELL!!!!!!!!!!!!!!!                             *
* Only run this on a machine that you can push the "reset" button!!!! *
*                                                                     *
* IF YOU BRING ANY SERVER DOWN SCC WILL LOCK YOUR ACCOUNT! and I will *
* not assist in your getting your account back.                       *
***********************************************************************

Create a C/C++ program that will us command-line arguments in 
conjunction with the fork() and exe*() system calls to create a fork 
bomb. 

The command line argument must be the name of an "X" program (such 
as xclock) to run (so you can watch it take over the computer). For
example "hw2 xclock" would execute via the fork() and exe*() systems 
call the xclock program. However, your program must also use the fork() 
and exe*() calls to execute a copy of hw2 with the same command-line 
arguments, creating the "fork bomb".

A successful form bomb will bring the computer to its knees, to the point
where you will probably have to press the reset button to stop it.

NOTE: Your program ***CANNOT*** use any type of loop. A program that 
uses a loop (of any kind) is not a true fork bomb and will earn you only 
a few points. No exceptions.


***********************************************************************
* DO NOT RUN THIS ON SHELL!!!!!!!!!!!!!!!                             *
* Only run this on a machine that you can push the "reset" button!!!! *
*                                                                     *
* IF YOU BRING ANY SERVER DOWN SCC WILL LOCK YOUR ACCOUNT! and I will *
* not assist in your getting your account back.                       *
***********************************************************************

REQUIREMENTS:
-------------
1. Your program must run in Streibel 109/115.

2. Your full name must appear as a comment at the beginning of your 
   program.

3. Your source code must be named hw3-yourname.c or hw3-yourname.cpp

4. Email your source (subject hw3-yourname) to rmarsh@cs.und.edu 
*/