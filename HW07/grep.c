/*
*	utils.c
*	Source code with some utilities used in homework nr.7 for Procedrual Programming
*	Author: Jiri Skoda
*			Student of Open Informatics
*			at Faculty of Electrical Engineering
*			of Czech Technical University in Prague
*
*	(c) Jiri Skoda 2017
*/


#include <stdio.h>
#include <stdlib.h>


#ifndef __UTILS_H__
#define __UTILS_H__

#define bool int
#define TRUE 1
#define FALSE 0

#define ERR -1

#define RED "[01;31m[K"
#define RESET "[m[K"

//Definitions of colors in shell
/*#define RED   "\x1B[1;31m"
#define GRN   "\x1B[1;32m"
#define YEL   "\x1B[1;33m"
#define BLU   "\x1B[1;34m"
#define MAG   "\x1B[1;35m"
#define CYN   "\x1B[1;36m"
#define WHT   "\x1B[1;37m"
#define RESET "\x1B[1;0m"*/

#ifndef MAX_LENGTH
#define MAX_LENGTH 256
#endif // !MAX_LENGTH

//Function to check if strin contains substring
bool containsString(char *longer_string, char *shorter_string)
{
	int len1 = 0;
	int len2 = 0;
	while (longer_string[len1] != '\0')
	{
		len1++;
	}
	while (shorter_string[len2] != '\0')
	{
		len2++;
	}

	if (len2 > len1)
	{
		return FALSE;
	}
	else
	{
		int index = 0;

		for (int i = 0; i < len1; i++)
		{
			if (longer_string[i] == shorter_string[index])
			{
				index++;
				if (index >= len2)
				{
					return TRUE;
				}
			}
			else
			{
				if (index >= len2)
				{
					return TRUE;
				}
				else
				{
					index = 0;
				}
			}
		}

	}
	return FALSE;


}

//Function to make from char[] string (ending with \0)
char* makeString(char *input)
{
	char* reti = (char *)malloc((MAX_LENGTH + 1) * sizeof(char));
	for (int i = 0; i < (MAX_LENGTH + 1); i++)
	{
		reti[i] = '\0';
	}
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		reti[i] = input[i];
	}
	return reti;
}

//Function to fill array with '\0'

void flush(char *input, int length)
{
	for (int i = 0; i < length; i++)
	{
		input[i] = '\0';
	}
}


void printColor(char *longer_string, char *shorter_string)
{

	int len1 = 0;
	int len2 = 0;

	int start = 0;

	int written = 0;


	while (longer_string[len1] != '\0')
	{
		len1++;
	}
	while (shorter_string[len2] != '\0')
	{
		len2++;
	}

	if (len2 > len1)
	{
		return;
	}
	else
	{
		int index = 0;
		for (int i = 0; i < len1; i++)
		{
			if (longer_string[i] == shorter_string[index])
			{
				if (index == 0 && (i > start || i == 0))
				{
					start = i;
				}
				index++;
			}

			if (index >= len2)
			{
				for (int x = written; x < start; x++)
				{
					printf("%c", longer_string[x]);
					written++;
				}

				printf(RED);
				for (int x = 0; x < len2; x++)
				{
					printf("%c", shorter_string[x]);
					written++;
				}
				printf(RESET);

				index = 0;
			}

		}

	}
	for (int i = written; i < len1; i++)
	{
		printf("%c", longer_string[i]);
	}
}

#endif // !__UTILS_H__


/*
*	grep.c
*	Main source code for homework nr.7 for subject Procedural Programming
*	Author: Jiri Skoda
*			Student of Open Informatics
*			at Faculty of Electrical Engineering
*			of Czech Technical University in Prague
*
*	(c) Jiri Skoda 2017
*/

#define MAX_LENGTH 256




//Main program
int main(int argc, char *argv[])
{
	/*if (argc < 3)
	{
	fprintf(stderr, "Error: Neplatne parametry!\n");
	return 101;
	}*/

	char *pattern = NULL;
	char *filename = NULL;
	bool color = FALSE;
	char *arg = makeString("--color=always");

	if (argc == 2)
	{
		pattern = argv[1];
	}
	else if (argc == 3)
	{
		pattern = argv[1];
		filename = argv[2];
	}
	else if (argc == 4 && containsString(argv[1], arg) == TRUE)
	{

		color = TRUE;
		pattern = argv[2];
		filename = argv[3];
	}
	free(arg);

	int written = 0;
	if (filename != NULL && color == FALSE)
	{
		FILE* file = fopen(filename, "r");
		char line[MAX_LENGTH];
		for (int i = 0; i < MAX_LENGTH; i++)
		{
			line[i] = '\0';
		}

		while (fgets(line, sizeof(line), file))
		{
			char *string_pattern = makeString(pattern);
			if (containsString(line, string_pattern) == TRUE)
			{
				printf("%s", line);
				written++;
			}
			free(string_pattern);

		}

		fclose(file);
	}
	else if (filename != NULL && color == TRUE)
	{

		FILE* file = fopen(filename, "r");
		char line[MAX_LENGTH];
		for (int i = 0; i < MAX_LENGTH; i++)
		{
			line[i] = '\0';
		}

		while (fgets(line, sizeof(line), file))
		{
			char *string_pattern = makeString(pattern);
			if (containsString(line, string_pattern) == TRUE)
			{
				printColor(line, string_pattern);
			}
			free(string_pattern);

		}

		fclose(file);
	}
	else
	{
		char input;
		int index = 0;
		char *line;
		while (scanf("%c", &input) != EOF)
		{
			if (index == 0)
			{
				line = (char *)malloc((MAX_LENGTH + 1) * sizeof(char));
				line[index] = input;
				index++;
			}
			else if (input == '\n')
			{

				char *string_pattern = makeString(pattern);
				if (containsString(line, string_pattern) == TRUE)
				{
					printf("%s\n", line);
					written++;
				}

				free(string_pattern);
				flush(line, (MAX_LENGTH + 1));
				free(line);
				index = 0;
			}
			else
			{
				line[index] = input;
				index++;
			}

		}

	}


	if (written == 0)
	{
		return 1;
	}


	return 0;

}