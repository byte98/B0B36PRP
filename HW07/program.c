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

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

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
				written++;
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