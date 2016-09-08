// CSci 451 HW 2
// Written by Chris Davis
// ID#: 0879026

#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
	char command[200];
	char link[200];
	char storage[200];
	strcpy(command, "wget -q http://towingnd.com");
	int temp = system(command); // This should download a file called "index.html"
	
	strcpy(command, "wget -q -U \"Mozilla/5.001\" -O - 'http://towingnd.com' | \
		perl -lne 'print$1while/<\\s*a\\s+href\\s*=\\s*[\"\\047]([^\"\\047]+)/ig'");
	temp = system(command); // This takes care of printing the links to the terminal
	strcat(command, " > output.txt");
	temp = system(command); // This puts the elements into a file named 'output.txt', with a line break after each
	FILE *fp;
	fp = fopen("output.txt", "r");
	if ( fgets(storage, 200, fp) != NULL) {
		strcpy(link, "http://towingnd.com/");
		strcat(link, storage); // The full link to the file we need to dl should now be sotred in 'link'
		strcpy(command, "wget -q ");
		strcat(command, link); // Should be the full wget command
		system(command);
	} else {
		printf("Critical failure: couldn't open 'output.txt'; does it exist?\n");
	}
	strcpy(command, "unlink index.html");
	system(command);
}