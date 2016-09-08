//This code was written by Chris Davis

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float EvilTwin(float u, float o, int x)
{
    float prob;
    float temp;
    float temp1;
    const float PI  =3.141592653589793238462;
    temp = sqrt(2 * PI);
    // printf("Evil: %lf ", temp);
    temp = 1/(o * temp);
    // printf("%lf ", temp);
    temp1 = -x + u;
    // printf("%lf ", temp1);
    temp1 = temp1 * temp1;
    // printf("%lf ", temp1);
    temp1 = temp1/(2 * (o * o));
    // printf("%lf ", temp1);
    // temp1 = -1 * temp;
    // printf("%lf ", temp1);
    prob = pow(temp, temp1);
    // printf("%lf \n", prob);
    return prob;
}

float NormalTwin(float u, float o, int x)
{
    float prob;
    float temp;
    float temp1;
    const float PI  =3.141592653589793238462;
    temp = sqrt(2 * PI);
    // printf("Normal: %lf ", temp);
    temp = 1/(o * temp);
    // printf("%lf ", temp);
    temp1 = -x + u;
    // printf("%lf ", temp1);
    temp1 = temp1 * temp1;
    // printf("%lf ", temp1);
    temp1 = temp1/(2 * (o * o));
    // printf("%lf ", temp1);
    // temp1 = -1* temp;
    // printf("%lf  ", temp1);
    prob = pow(temp, temp1);
    // printf("%lf \n", prob);
    return prob;
}

int main()
{
    int random = rand() %36;
    float etu = 27;
    float eto = 4.2;
    float ntu = 17;
    float nto = 6;
    float pa;
    float pb;
    float p;
    float ptemp;
    int n;
    
    for (n = 0; n < 5000; n++)
    {
        pa = EvilTwin(etu,eto,random);
        pb = NormalTwin(ntu,nto,random);
        p = pa * pb;
        ptemp = ptemp + p;
        random = rand() %36;
        // printf ("%d ", random); && THIS WORKS &&
    }
    // for loop for probability simulation
    
    p = ptemp / n;
    // Divide total probabilities by number of iterations
    
    printf("Evil Twin's u = %g\n", etu);
    printf("Evil Twin's o = %g\n", eto);
    printf("Normal Twin's u = %g\n", ntu);
    printf("Normal Twin's o = %g\n", nto);
    printf("The total number of iterations = %d\n", n);
    printf("The final probability is: %g\n", p);
    return 0;
}

