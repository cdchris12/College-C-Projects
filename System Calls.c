//This code was written by Chris Davis

//This code works best when ran as the root user due to the nature of the system calls within.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int main()
{
	//Code goes here
	/*printf("Making the JUNK directory...\n");
	system("mkdir JUNK");
	
	printf("Navigating to the JUNK directory...\n");
	system("cd JUNK");
	
	printf("Copying the contents of the /etc/ directory...\n");
	system("cp /etc/* .");
		
	printf("Listing all filenames that start with R...\n");
	system("ls r* > listR");
		
	printf("Listing all filenames that start with A...\n");
	system("ls a* > listA");
		
	printf("Listing all filenames that start with M...\n");
	system("ls m* > listM");
		
	printf("Removing all files whose names begin with R...\n");
	system("rm r*");
		
	printf("Removing all files whose names begin with A...\n");
	system("rm a*");
		
	printf("Removing all files whose names begin with M...\n");
	system("rm m*");
		
	printf("Listing all other files...\n");
	system("ls * > listX");
		
	printf("Copying listR as the main list...\n");
	system("cat listR > list");
		
	printf("Concatenating listA with the main list...\n");
	system("cat listA >> list");
		
	printf("Concatenating listM with the main list...\n");
	system("cat listM >> list");
		
	printf("Concatenating listX with the main list...\n");
	system("cat listX >> list");
	
	printf("Sorting the file list...\n");
	system("sort list > sorted");
		
	printf("Copying the sorted list to the previous directory...\n");
	system("cp sorted ..");
		
	printf("Changing to the parent directory...\n");
	system("cd ..");
		
	printf("Removing temporary files...\n");
	system("rm -rf JUNK");
	
	return (1);*/
	
	system(	"mkdir JUNK; cd JUNK; cp /etc/* .; ls r* > listR; ls a* > listA; ls m* > listM; rm r*; rm a*; rm m*; ls * > listX; cat listR > list; cat listA >> list; cat listM >> list; cat listX >> list; sort list > sorted; cp sorted ..; cd ..; rm -rf JUNK" );
	return (1);
}



/*HW-1	CS451	10 points	Due: Monday, May 26

Part 1 (5 points):
Write a C program on a LINIX machine that uses the system call "system" to
execute UNIX commands. Your program must execute the following commands all 
via the UNIX "system" call:

mkdir JUNK
cd JUNK
//cp /etc/* .
ls r* > listR
ls a* > listA
ls m* > listM
rm r*
rm a*
rm m*
ls * > listX
cat listR > list
cat listA >> list
cat listM >> list
cat listX >> list
sort list > sorted
cp sorted ..
cd ..
rm -rf JUNK

* See the unix "man" pages on system - i.e. "man system" - for info on the 
system command.

Part 2 (5 points):
Why is the sorted result (the file "sorted") is as it is?


REQUIREMENTS:
-------------
1. Your program must run in Streibel 109/115.

2. Your full name must appear as a comment at the beginning of your 
   program.

3. Your source code must be named hw1-yourname.c or hw1-yourname.cpp

4. Include your explanation for part 2 in your email.

5. Email your source (subject hw1-yourname) to rmarsh@cs.und.edu */