//This code was written by Chris Davis

#include<stdio.h>
#include<math.h>
 
int main()
{
    double r,B,P; 
    double I [100]; //May need to get bigger eventually, but should be fine for this project
    int n = 1;
    //printf("Enter the interest rate as a decimal:\n");
    //scanf("%g",&r); //Obsolete for this code.
    r = .22;
   
    //printf("Enter the amount borrowed:\n");
    //scanf("%g",&B); //You could have the borrower set their own amount borrowed with this code
    B = 5000;
   
    printf("Enter the desired payment amount:\n");
    scanf("%lf", &P); //Allow user to set own payment amount
   
    printf("Your interest rate is: ");
    double temp = r * 100;
    printf("%g", temp);
    printf("%%\n");
    printf("Your initial balance is: %g\n", B);
    printf("Your monthly payment is: %g\n", P);
   
    I[0] = (r/12)*B;
    //B -= (P-I[0]);
    printf("Month    Interest      Balance\n");
    printf("%d        %.2f       %.2f\n", n,I[0],B);
   
    while (1)
    {
		I[n] = (r/12)*(B-P+I[n-1]);
		B -= (P-I[n-1]);
        if (B<0)
            break;
		n++;
		printf("Month    Interest      Balance\n");
		printf("%d        %.2f       %.2f\n", n,I[n-1],B);
	}
    
    //for (n=25)
   
    return 0;
}

/*Create a C program that will calculate the interest paid on 
a loan. The equations we will use are:

     I[o] = (r/12)*B
     I[n] = (r/12)*(B-P+I[n-1])

Where:
     r is the anual interest rate (assume 22% or 0.22).
     B is the amount borrowed (assume $5000).
     P is the payment amount (pick some value).
     I[o] is the interest due after the first month.
     I[n] is the interest due after the nth month.

Your program must prompt the user for the monthly payment that
they wish to make. Your program must then display the interest 
rate (r), the initial balance (B), the monthly payment (P). 
Your program must then produce a month-by-month table showing the
month, the interest due/paid each month and the remaining balance.

The table must take the user to the payoff-point (where balance 
becomes zero or negative). Finally the program must display the 
total interest paid over the life of the loan.

Example:
--------
Enter your monthly payment: 500

r = 0.22
B = 5000.0
P = 500.0

1 91.67 5000.00
2 84.18 4591.67
3 76.56 4175.85
4 68.79 3752.40
5 60.89 3321.20
6 52.84 2882.09
7 44.64 2434.93
8 36.29 1979.57
9 27.79 1515.86
10 19.13 1043.65
11 10.32 562.78
12  1.34 73.10
 
Total interest paid: 574.44



CONCERNS:
---------
1. Watch the data types!*/