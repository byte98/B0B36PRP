//includes if externl libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define LIMIT 1000000 // definition for maximum expected divisor of input

// global variables
static int primes[LIMIT];
static int divisors[LIMIT];

// definitions of functions
void sieveOfEratosthenes(int limit);
void printPrimes(char only_true);
void computeDivisors(long long input);
void printDivisors();

/* The main program */
int main(int argc, char *argv[])
{

    sieveOfEratosthenes(LIMIT);  // call function to compute primes (it will be done only once in whole program to save resources)

    long long input = 0;
    while (scanf("%lli",&input) == 1)
    {
        if (input >= 1) // check if correct input was loaded
        {
            printf("Prvociselny rozklad cisla %lli je:\n", input);
            if (input == 1) // special case (number 1)
            {
                printf("1");
            }
            else
            {
                computeDivisors(input);
                printDivisors();
            }
            printf("\n");
        }
        else if (input == 0) // the only correct end of program is input 0
        {
            return 0;
        }
        else
        {
            fprintf(stderr, "Error: Chybny vstup!\n");            
            return 100;
        }
    }
    fprintf(stderr, "Error: Chybny vstup!\n");

    return 100;
}

// function to compute primes using Sieve of Eratosthenes
void sieveOfEratosthenes(int limit)
{
    //set 0 and 1 is not prime number
    primes[0] = 0;
    primes[1] = 0;

    //set default values for numbers 2 to limit is prime number
    for (int i = 2; i <= limit; i++)
    {
        primes[i] = 1;
    }

    //Sieve of Eratosthenes
    for (int i = 2; i <= limit; i++)
    {
        if (primes[i] == 1)
        {
            for (int c = (2 * i); c <= limit; c+= i)
            {
                primes[c] = 0;
            }
        }
    }

}

// function to print primes (just for debugging)
void printPrimes(char only_true)
{
    if (only_true == 0)
    {
        for (int i = 0; i < (sizeof(primes) / sizeof(primes[0])); i++)
        {
            if (primes[i] == 0)
            {
                printf("%9i: FALSE\n", i);
            }
            else
            {
                printf("%9i: TRUE\n", i);
            }
        }
    }
    else
    {
        for (int i = 0; i < (sizeof(primes) / sizeof(primes[0])); i++)
        {
            if (primes[i] != 0)
            {
                printf("%i\n", i);
            }
        }
    }
}

// function to compute divisors of number
void computeDivisors(long long input)
{
    int index = 0;
    //set default values for divisors
    for (int i = 0; i < (sizeof(divisors) / sizeof(divisors[0])); i++)
    {
        divisors[i] = 0;
    }

    //computing divisors
    for (int i = 0; i < (sizeof(primes) / sizeof(primes[0])); i++)
    {
        if (primes[i] == 1)
        {
            while (input % i == 0)
            {
                divisors[index] = i;
                input /= i;
                index ++;
            }
        }
    }
    if (input != 1)
    {
        divisors[index] = input;
    }
}

// function to print formated divisors
void printDivisors()
{
    char first = 1;
    int number = divisors[0];
    char number_count = 0;
    int i = 0;
    
    while (divisors[i] != 0)
    {
        if (divisors[i] == number)
        {
            number_count ++;
        }
        else
        {
            if (first == 0)
            {
                printf(" x ");
            }
            else
            {
                first = 0;
            }

            printf("%i", number);
            if(number_count > 1)
            {
                printf("^%i", number_count);
            }
            number = divisors[i];
            number_count = 1;
        }
        i++;
    }

    if (first == 0)
    {
        printf(" x ");
    }
    else
    {
        first = 0;
    }
 
    printf("%i", number);
    if(number_count > 1)
    {
        printf("^%i", number_count);
    }

}


