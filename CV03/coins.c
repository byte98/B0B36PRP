#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int coin_function(int input, int value)
{
    if ((int)floor(input/value) != 0)
    {
        printf ("%i * %i Kč\n", (int)floor(input / value), value);
    }
    
    return (input % value);
}


int main(int argc, const char * argv[])
{
    int input = 0;
    if (scanf("%i",&input) == 1)
    {

        //input = coin_function(input, 50);
        input = coin_function(input, 20);
        input = coin_function(input, 10);
        input = coin_function(input, 5);
        input = coin_function(input, 2);
        if (input != 0)
        {
            printf("%i * 1 Kč\n", input);
        }    

    }
}
