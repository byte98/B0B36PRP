#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
  int width = 0;
  int height = 0;
  int fence = 0;

  int inputs = scanf("%i%i", &width, &height);
  if (width == height)
  {
    if(scanf("%i", &fence) == 1)
    {
      inputs = 3;
    }
    else
    {
      fprintf(stderr,"Error: Chybny vstup!\n");
      return 100;
    }
  }

  //compulsory assignment
  if (inputs == 2)
  {
    if ((width < 3 || width > 69) || (height < 3 || height > 69))
    {
      fprintf(stderr,"Error: Vstup mimo interval!\n");
      return 101;
    }
    else if(width % 2 == 0)
    {
      fprintf(stderr,"Error: Sirka neni liche cislo!\n");
      return 102;
    }
    else
    {
      int chars = (width / 2);
      int space = 1;
      int line = 1;

      //printing roof
      while (chars > 0)
      {
        if (line == 1)
        {
          for (int c = 1; c<= chars; c++)
          {
            printf(" ");
          }
          printf("X");
          chars --;
          line ++;
        }
        else
        {
          for (int c = 1; c<= chars; c++)
          {
            printf(" ");
          }
          printf("X");
          chars --;
          line ++;
          for (int c = 1; c<= space; c++)
          {
            printf(" ");
          }
          printf("X");
          space += 2;
        }
        printf("\n");
      }

      //printing house
      for (int c = 1; c <= width; c++)
      {
        printf("X");
      }
      printf("\n");
      for (int c = 1; c <= (height - 2); c++)
      {
        printf("X");
        for (int i = 1; i <= (width - 2); i++)
        {
          printf(" ");
        }
        printf("X\n");
      }
      for (int c = 1; c <= width; c++)
      {
        printf("X");
      }
      printf("\n");
    }
  }

  //optional assignment
  else if(inputs == 3 && height == width)
  {

    if ((width < 3 || width > 69) || (height < 3 || height > 69))
    {
      fprintf(stderr,"Error: Vstup mimo interval!\n");
      return 101;
    }
    else if(width % 2 == 0)
    {
      fprintf(stderr,"Error: Sirka neni liche cislo!\n");
      return 102;
    }
    else if (fence >= height || fence < 1)
    {
      fprintf(stderr,"Error: Neplatna velikost plotu!\n");
      return 103;
    }
    else
    {
      int chars = (width / 2);
      int space = 1;
      int line = 1;

      //printing roof
      while (chars > 0)
      {
        if (line == 1)
        {
          for (int c = 1; c<= chars; c++)
          {
            printf(" ");
          }
          printf("X");
          chars --;
          line ++;
        }
        else
        {
          for (int c = 1; c<= chars; c++)
          {
            printf(" ");
          }
          printf("X");
          chars --;
          line ++;
          for (int c = 1; c<= space; c++)
          {
            printf(" ");
          }
          printf("X");
          space += 2;
        }
        printf("\n");
      }

      //printing house with fence
      char house_char = 'o';
      char fence_char = '-';
      line = 1;
      for(int c = 1; c <= width; c++)
      {
        printf("X");
      }
      printf("\n");
      while (line <= (height - 2))
      {
        if (line % 2 == 0)
        {
          house_char = '*';
        }
        else if (line % 2 != 0)
        {
          house_char = 'o';      
        }
        printf("X");
        for(int c = 1; c <= (width - 2); c++)
        {
          printf("%c", house_char);
          if (house_char == 'o')
          {
            house_char = '*';
          }
          else if (house_char == '*')
          {
            house_char = 'o';
          }
        }
        printf("X");
        if (line >= (height - fence))
        {
          //print fence
          if ((line == (height - fence)) || (line == height))
          {
            if (fence % 2 == 0)
            {
              fence_char = '-';
            }
            else if (fence % 2 != 0)
            {
              fence_char = '|';
            }
            for (int c = 1; c <= fence; c++)
            {
              printf("%c", fence_char);
              if (fence_char == '-')
              {
                fence_char = '|';
              }
              else if (fence_char == '|')
              {
                fence_char = '-';
              }
            }
          }
          else
          {
            if (fence % 2 == 0)
            {
              fence_char = ' ';
            }
            else if (fence % 2 != 0)
            {
              fence_char = '|';
            }
            for (int c = 1; c <= fence; c++)
            {
              printf("%c", fence_char);
              if (fence_char == ' ')
              {
                fence_char = '|';
              }
              else if (fence_char == '|')
              {
                fence_char = ' ';
              }
            }
          }
        }
        printf("\n");
        line++;
      }
      for(int c = 1; c <= width; c++)
      {
        printf("X");
      }
      if (fence % 2 == 0)
      {
        fence_char = '-';
      }
      else if (fence % 2 != 0)
      {
        fence_char = '|';
      }
      for (int c = 1; c <= fence; c++)
      {
        printf("%c", fence_char);
        if (fence_char == '-')
        {
          fence_char = '|';
        }
        else if (fence_char == '|')
        {
          fence_char = '-';
        }
      }
      printf("\n");
      
    }

  }
  else
  {
    fprintf(stderr,"Error: Chybny vstup!\n");
    return 100;
  }
  
  return 0;
}

