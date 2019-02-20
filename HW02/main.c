#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
  //loading inputs
  int input = 0;
  int count = 0;
  int positive_numbers = 0;
  int negative_numbers = 0;
  int even_numbers = 0;
  int odd_numbers = 0;
  int max = 0;
  int min = 0;
  int sum = 0;
  while (scanf("%d",&input) == 1)
  {
    count++;
    sum += input;
    if (input < -10000 || input > 10000)
    {
      printf("\nError: Vstup je mimo interval!\n");
      return 100;
    }
    else
    {
      if (count == 1)
      {
        printf("%d", input);
      }
      else
      {
        printf(", %d", input);
      }
      if (input % 2 == 0)
      {
        even_numbers++;
      }
      else
      {
        odd_numbers++;
      }
      if (max == 0)
      {
        max = input;
      }

      if (min == 0)
      {
        min = input;
      }

      if (input > max)
      {
        max = input;
      }

      if (input < min)
      {
        min = input;
      }

      if (input > 0)
      {
        positive_numbers++;
      }

      if (input < 0)
      {
        negative_numbers++;
      }
    }
  }

  float positive_percent = ((float)positive_numbers / (float)count) * 100;
  float negative_percent = ((float)negative_numbers / (float)count) * 100;
  float even_percent = ((float)even_numbers / (float)count) * 100;
  float odd_percent = ((float)odd_numbers / (float)count) * 100;
  float avg = ((float)sum / (float)count);

  printf("\nPocet cisel: %i", count);
  printf("\nPocet kladnych: %i", positive_numbers);
  printf("\nPocet zapornych: %i", negative_numbers);
  printf("\nProcento kladnych: %.2f", positive_percent);
  printf("\nProcento zapornych: %.2f", negative_percent);
  printf("\nPocet sudych: %i",even_numbers);
  printf("\nPocet lichych: %i",odd_numbers);
  printf("\nProcento sudych: %.2f", even_percent);
  printf("\nProcento lichych: %.2f", odd_percent);
  printf("\nPrumer: %.2f", avg);
  printf("\nMaximum: %i", max);
  printf("\nMinimum: %i\n", min);
  return 0;
}

