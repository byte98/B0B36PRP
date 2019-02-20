/*
caesar.h
Source code with some useful functions solving Caesar's cipher.
Author: Jiøí Škoda
		student of
		Open Informatics
		at
		Faculty of Electrical Engineering
		at
		Czech Techical Universtity in Prague
*/

#ifndef CAESAR_INCLUDE
#define CAESAR_INCLUDE


#include "utility.h"
#include "dynamic.h"
#include "caesar.log.h"

//Function to shift letter
char shiftLetter(char letter, int direction)
{
	char reti = letter;
	reti += direction;
	if (reti < 65)      //check if letter after shift is at least A (65)
	{
		direction += (letter - 65);
		reti = (122 + direction) + 1;
	}

	if (reti > 122)     //check if letter after shift is max z (122)
	{
		reti = 65 + (direction - (122 - letter));
		reti -= 1;
	}

	if (reti > 90 && reti < 97) //check if leter is not in space of ASCII table between Z (90) and a (97)
	{
		if (direction > 0)
		{
			reti = 97 + (direction - (90 - letter));
			reti -= 1;
		}
		else
		{
			reti = 90 + (direction + (letter - 97));
			reti += 1;
		}
	}

	return reti;
}


//Procedure to shift array
void pShiftArray(char *input, int count, int direction)
{
	for (int i = 0; i < count; i++)
	{
		input[i] = shiftLetter(input[i], direction);
	}
}

//Procedure to shift array accepting array struct
void shiftArray(array input, int direction)
{
	pShiftArray(input.data, input.count, direction);
}

//Function to check validity of char
bool isValid(char input)
{
	if ((input >= 65 && input <= 90) || (input >= 97 && input <= 122))
	{
		return TRUE;
	}

	return FALSE;
}

//Function to check validity of array
bool checkArray(array input)
{
	bool reti = TRUE;

	for (int i = 0; i < input.count; i++)
	{
		if (reti == TRUE)
		{
			reti = isValid(input.data[i]);
		}

		if (reti == FALSE)
		{
			break;
		}
	}

	return reti;

}

//Function to get count of same letters
int getSameLetters(array string1, array string2)
{
	int reti = 0;
	int count;

	count = string1.count < string2.count ? string1.count : string2.count;

	for (int i = 0; i < count; i++)
	{
		if (string1.data[i] == string2.data[i])
		{
			reti++;
		}
	}

	return reti;
}

//Function to decode message
array decodeSimple(array encoded, array decoded, bool log)
{

	if (log == TRUE)
	{
		printSimpleHeader(encoded, decoded);
		printSimpleTableHeader();
	}

	int r = 1;

	array reti = copyArray(encoded);
	int best_match = getSameLetters(encoded, decoded);

	if (log == TRUE)
	{
		printSimpleRow(r, reti, best_match);
	}

	for (int i = 0; i < 52; i++)
	{
		r++;
		shiftArray(encoded, 1);
		int match = getSameLetters(encoded, decoded);
		if (match > best_match)
		{
			best_match = match;
			freeArray(reti);
			reti = copyArray(encoded);
		}

		if (log == TRUE)
		{
			printSimpleRow(r, encoded, match);
		}
	}

	r++;

	if (log == TRUE)
	{
		printResultHeader();
		printSimpleRow(r, reti, best_match);
		printResult(encoded, reti, 0);
	}

	return reti;
}

//Function to compute Levenshtein Distance of two strings
int getLevenshteinDistance(array string1, array string2)
{

	int** matrix;

	matrix = malloc(string1.count * sizeof(int*));
	for (int i = 0; i < string1.count; i++) {
		matrix[i] = malloc(string2.count * sizeof(int));
	}



	for (int i = 0; i < string1.count; i++)
	{
		matrix[i][0] = i;
	}

	for (int i = 0; i < string2.count; i++)
	{
		matrix[0][i] = i;
	}

	for (int i = 1; i < string1.count; i++)
	{
		for (int j = 1; j < string2.count; j++)
		{
			if (string1.data[i] == string2.data[j])
			{
				matrix[i][j] = matrix[(i - 1)][(j - 1)];
			}
			else
			{
				int nums[] = { (matrix[(i - 1)][j] + 1) , (matrix[i][(j - 1)] + 1) , (matrix[(i - 1)][(j - 1)] + 1) };
				matrix[i][j] = getMin(nums, 3);

			}

		}
	}

	int reti = matrix[(string1.count - 1)][(string2.count - 1)];


	for (int i = 0; i < string1.count; i++) {
		free(matrix[i]);
	}
	free(matrix);
	return reti;
}

//Function to decode message using Levenshtein Distance
array decodeAdvanced(array encoded, array decoded, bool log)
{

	if (log == TRUE)
	{
		printAdvancedHeader(encoded, decoded);
		printAdvancedTableHeader();
	}

	int r = 1;
	array reti = copyArray(encoded);
	int lowest_ld = getLevenshteinDistance(encoded, decoded);

	if (log == TRUE)
	{
		printAdvancedRow(r, reti, getSameLetters(encoded, decoded),lowest_ld);
	}

	for (int i = 0; i < 52; i++)
	{
		r++;
		shiftArray(encoded, 1);
		int ld = getLevenshteinDistance(encoded, decoded);
		if (ld < lowest_ld)
		{
			lowest_ld = ld;
			freeArray(reti);
			reti = copyArray(encoded);
		}

		if (log == TRUE)
		{
			printAdvancedRow(r, encoded, getSameLetters(encoded, decoded), ld);
		}
	}

	r++;

	if (log == TRUE)
	{
		printResultHeader();
		printAdvancedRow(r, reti, getSameLetters(reti, decoded), lowest_ld);
		printResult(encoded, reti, 0);
	}

	return reti;
}





#endif
