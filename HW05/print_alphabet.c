#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    static char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    int input = 0;
    scanf("%i", &input);

    for (int i = 0; i < input; i++)
    {
        if (alphabet[i % 52] != '\0')
        {
            printf("%c", alphabet[i % 52]);
        }
    }

    return 0;
}
