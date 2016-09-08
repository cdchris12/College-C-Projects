#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct List {
    char first[42];
    char last[42];
    char number[13];
};

// Program starts here
int main (void)
{
    int i, j, a, b, result, ac;
    char mod;
    char fName[42], lName[42], phoneNumber[13];
    
    FILE *data;
    
    // Determine the size of the input file
    data = fopen("./hw4.data", "r");
    int count = 0, count2 = 0;
    while (1)
    {
        fscanf(data, "%c %s %s %s\n", &mod, fName, lName, phoneNumber);
        //printf("%c %s %s %s \n", mod, fName, lName, phoneNumber);
        if (feof(data)) break;
        count++;
    }
    
    // Create the INITIAL, 10 structure long, array of structures
    // This line only exists to ensure I meet the requirements of the homework assignment.
    struct List *stuff = (struct List *)calloc(10, sizeof(struct List));
    struct List *temp = (struct List *)calloc(2, sizeof(struct List));
    free(stuff);// Immediately release it from memory
    free(temp);
    //printf("%c %s %s %s \n", mod, fName, lName, phoneNumber);
    
    // Create the dynamicly sized array of structures
    stuff = (struct List *)calloc(count+1, sizeof(struct List));
    temp = (struct List *)calloc(2, sizeof(struct List));
    //printf("%c %s %s %s \n", mod, fName, lName, phoneNumber);
    
    // Populate dynamic array
    rewind(data);
    //printf("%c %s %s %s \n", mod, fName, lName, phoneNumber);
    
    j = 0;
    for (i=0; i<=count; i++)
    {
        fscanf(data, "%c %s %s %s\n", &mod, fName, lName, phoneNumber);
        
        //printf("%c", mod);
        // Test the variable for possible actions
        if (mod == 'I') // Insert the person into the array
        {
            //printf("%c %s %s %s \n", mod, fName, lName, phoneNumber);
            strcpy(stuff[j].first, fName);
            strcpy(stuff[j].last, lName);
            strcpy(stuff[j].number, phoneNumber);
                        
            //printf("%s %s %s \n", stuff[j].first, stuff[j].last, stuff[j].number);
            j++;
            count2++;
        }
        else if (mod == 'D') // Delete the person from the array
        {
            //del(fName, lName, phoneNumber); // Need to implement this function
            for (a=0; a < count2; a++)
            {
                result = strcmp(fName, stuff[a].first);
                if (result == 0)
                {
                    result = strcmp(lName, stuff[a].last);
                    if (result == 0)
                    {
                        for (b = a; b < count2; b++)
                        {
                            strcpy(stuff[b].first, stuff[b+1].first);
                            strcpy(stuff[b].last, stuff[b+1].last);
                            strcpy(stuff[b].number, stuff[b+1].number);
                            
                        }
                        printf("\n%s %s was deleted from the circle of friends. Sad day for %s.\n\n", fName, lName, fName);
                        //count2--;
                        break;
                    }
                }
            }
        }
        else if (mod == 'P') // Print the list
        {
            int a = 0, b = 0;
            int result;
            //int count2 = count;
            
            // Sort the list
            for (a = 0; a < count2; a++)
            {
                for (b = 0; b < count2-1; b++)
                {
                    result = strcmp(stuff[b].first, stuff[b+1].first);
                    //printf("%d\n", result);
                    if (result > 0)
                    {
                        strcpy(temp[0].first, stuff[b].first);
                        strcpy(temp[0].last, stuff[b].last);
                        strcpy(temp[0].number, stuff[b].number);
                        
                        strcpy(stuff[b].first, stuff[b+1].first);
                        strcpy(stuff[b].last, stuff[b+1].last);
                        strcpy(stuff[b].number, stuff[b+1].number);
                        
                        strcpy(stuff[b+1].first, temp[0].first);
                        strcpy(stuff[b+1].last, temp[0].last);
                        strcpy(stuff[b+1].number, temp[0].number);
                    }
                    if (result == 0) // Just in case the first names are the same, sort by last name
                    {
                        //printf("Trouble");
                        result = strcmp(stuff[b].last, stuff[b+1].last);
                        if (result > 0)
                        {
                            strcpy(temp[0].first, stuff[b].first);
                            strcpy(temp[0].last, stuff[b].last);
                            strcpy(temp[0].number, stuff[b].number);
                            
                            strcpy(stuff[b].first, stuff[b+1].first);
                            strcpy(stuff[b].last, stuff[b+1].last);
                            strcpy(stuff[b].number, stuff[b+1].number);
                            
                            strcpy(stuff[b+1].first, temp[0].first);
                            strcpy(stuff[b+1].last, temp[0].last);
                            strcpy(stuff[b+1].number, temp[0].number);    
                        }
                        else if (result == 0) // Inserting the same name twice
                        {
                            // Do nothing
                        }
                    }
                }
            }
            
            printf("\nThe array is currently: \n\n");
            
            // Print the list
            for (a = 0; a<count2; a++)
            {
                printf("%s %s %s \n", stuff[a].first, stuff[a].last, stuff[a].number);
            }
        }
    }
    free(stuff); // Free the dynamic array
    free(temp);
    return 0;
}


// Assignment Info

/*
Write a program to manage a "circle of friends." Your
program must create a single dynamic array of structs
of length 10 to start. Your program must then open a
file (hw4.data) and add or delete entries as required
(see below). The file will have the following format:

x Ron Marsh 701-222-3333
x Dave Marsh 218-444-6666
x Radell Marsh 701-235-8133
x Brenda Marsh 701-277-5050
x Kia Marsh 701-275-1234
x Triston Marsh 701-275-0987

Where "x" will be "I", "D", or "P". "I" indicates that
the contact must be added to the contact pool, while "D"
indicates that the contact be removed from the contact
pool. "P" indicates places where you must print out the
entire contact list (there may be several "P"'s in the
                     actual file).

The test file will have more than 10 entries, so you
will have to dynamically adjust the array size (you CANNOT
                                                use realloc! - unless you want 1/2 credit). Also, your array
cannot be larger then the data set size + 3. So you will
have possibly to adjust the array size when you add and
delete contacts.

FInally, your list of contacts must be sorted by the first
name (A - Z).


REQUIREMENTS:
-------------
1. Your program must run in Streibel 109 or on shell.aero.und.edu.

2. Your full name must appear as a comment at the beginning of your
program.

3. Your source code must be named hw4-yourname.c

4. Email your source (subject hw4-yourname) to rmarsh@cs.und.edu and to
ivyjoy.serrano@my.und.edu */ 