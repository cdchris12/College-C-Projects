//This code was written by Chris Davis

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

char x;
int *temp, *temp2;
char outputTemp[] = {'H','W',' ','3',' ','i','n','p','u','t',':',' '};
char *output;
int i;
int arraySize;

int Resize(void)
{
    x = getch();
    printf("%c", x);
    if (arraySize % 2) //if arraySize is odd
    {
        temp[arraySize]=x;
        arraySize++;
        free(temp2);
        temp2=calloc(arraySize, sizeof(int));
        memcpy(temp2, temp, ((arraySize+1) * sizeof(int)));
        return *temp2;
    }
    else //if arraySize is even
    {
        temp2[arraySize]=x;
        arraySize++;
        free(temp);
        temp=calloc(arraySize, sizeof(int));
        memcpy(temp, temp2, ((arraySize+1) * sizeof(int)));
        return *temp;
    }
    
}

int getch(void) //Dynamic String Input function from Daniweb.com
{
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt); //store old settings
    newt = oldt; // copy old settings to new settings
    newt.c_lflag &= ~(ICANON | ECHO); // make one change to old settings in new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); //apply the new settings immediatly
    ch = getchar(); // standard getchar call
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // reapply the old settings
    return ch; // return received char
}

int main(void)
{
    x = ' ';
    arraySize = 0;
    printf("Enter characters: ");
    temp=calloc(1, sizeof(int));
    if (temp == NULL) exit(1);
    
    temp2=calloc(1, sizeof(int));
    
    if (temp2 == NULL) exit(1);
    
    
    while (x != '\n') // Get and resize the arrays dynamically
    {
        Resize();
    }
    
    printf("Total Characters: %d\n", arraySize-1);
    
    // Begin printing out the arrays
    
    if (arraySize % 2)
    {
        arraySize++;
        //free(temp);
        //temp=calloc(arraySize, sizeof(arraySize));
        //memcpy(temp, temp2, sizeof(temp));
        //temp[arraySize] = '\0';
        int totalSize = arraySize + 12;
        output=calloc(totalSize+10, sizeof(int));
        memcpy(output, outputTemp, sizeof(outputTemp));
        memcpy(output+13, temp, ((arraySize-1) * sizeof(int)));
        printf ("%c\n", output[15]);
        for (i = 0; i <= totalSize; i++) {
            printf("%c", output[i]);
        }
    }
    else
    {
        arraySize++;
        //free(temp2);
        //temp2=calloc(arraySize, sizeof(arraySize));
        //memcpy(temp2, temp, sizeof(temp2));
        //temp2[arraySize] = '\0';
        int totalSize = arraySize + 12;
        output = calloc(totalSize+10, sizeof(int));
        memcpy(output, outputTemp, sizeof(outputTemp));
        memcpy(output+13, temp2, ((arraySize-1) * sizeof(int)));
        printf ("%c\n", output[15]);
        for (i = 0; i <= totalSize; i++) {
            printf("%c", output[i]);
        }
    }

    // If you made it this far, you'll realize that it doesn't print out the entire string contents. I don't know why that is; the code all looks right to me. It also doesn't accept strings longer than 13 characters. Irregardless; partial credit is better than no credit!
    

}

/*
1.) Prompt for character input

2.) As characters are entered, call "vector function" to automatically adjust the array size.

3.) Use malloc / calloc to create/adjust the array

4.) memcpy?

5.) Return a pointer (to the array) and a copy of the array from the function to the main routine.

6.) Adjust the array 1 character at a time.

7.) When user just presses return (doesn't enter a character), append "\0" to the end (making it a string).

8.) Append the new string to the string: "HW 3 input: "

9.) Print the resulting string.
*/

/*
 C++ has a nice vector class that automatically adjusts the
 array size as needed. C does not have any such feature (until
 now :) ).
 
 Write a program that prompts the user for characters (not
 strings!). As the user enters characters your program must
 call the "vector function" (that you must write) to automatically
 adjust the character array size to hold the input.
 
 The function must use malloc/calloc to create/adjust the array
 size. You CANNOT use realloc!
 
 You may also want to read the man page on memcpy.
 
 The function must return a pointer (to the array) to the main
 routine (you will probably want to pass in the array also).
 
 You can adjust the array in chunks of 5 or 10 characters (vs 1
 character) if you want.
 
 When the user enters "return" (in place of a character) your
 program must append the '\0' character to the end (making it a
 string). Your program must then append the new string to the
 text/string "HW 3 input: " (be carefull here). Your program must
 then print out the resulting string.
 */

