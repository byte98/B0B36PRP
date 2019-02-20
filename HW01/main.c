#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
  int numberA;
  int numberB;
  
      if (scanf("%i %i", &numberA, &numberB) == 2) //test if two inputs were typed by user
      {
          if ((numberA < -10000 || numberA > 10000)||(numberB < -10000 || numberB > 10000))
          {
              printf("Vstup je mimo interval!\n");
              return 0;            
          }
          else
          {
              printf("Desitkova soustava: %i %i\n", numberA, numberB);
              printf("Sestnactkova soustava: %x %x\n", numberA, numberB);
              printf("Soucet: %i + %i = %i\n", numberA, numberB, (numberA + numberB));
              printf("Rozdil: %i - %i = %i\n", numberA, numberB, (numberA - numberB));
              printf("Soucin: %i * %i = %i\n", numberA, numberB, (numberA * numberB));
              if (numberB != 0)
              {
                printf("Podil: %i / %i = %i\n", numberA, numberB, numberA / numberB);
              }
              else
              {
                printf("Nedefinovany vysledek!\n");
              }
              float avg = ((float)numberA + (float)numberB)/2;

              printf("Prumer: %.1f\n", avg);

          }
      }
      else
      {
        printf("Vstup je mimo interval!\n");
      }
  
  return 0;
}

