/*
caesar.log.h
Source code with functions to log proccess of Caesar's cipher decoding
Author: Jiøí Škoda
		student of
		Open Informatics
		at
		Faculty of Electrical Engineering
		at
		Czech Techical Universtity in Prague
*/

#ifndef WIDTH
#define WIDTH 96
#endif // !WIDTH



#ifndef CAESAR_LOG_INCLUDE
#define CAESAR_LOG_INCLUDE


#include "utility.h"

void printSimpleHeader(array encoded, array decoded)
{
	printNtimes('*', WIDTH);
	printf("\n\n");
	setColor("white");
	printCenterSpaces(19, WIDTH);
	printf("SIMPLE DECODING LOG\n\n");
	resetColor();
	printNtimes(' ', 1);
	printColor(makeArray("SETTINGS:", 10), "yellow");
	resetColor();
	printf("\n");
	setColor("white");
	printf("ENCODED MESSAGE:");
	resetColor();
	printf("\n");
	printArray(encoded);
	printf("\n");
	setColor("white");
	printf("PARTLY DECODED MESSAGE:");
	printf("\n");
	resetColor();
	printArray(decoded);
	printf("\n\n");
	printNtimes('-', WIDTH);
	printf("\n");
	printCenterSpaces(26, WIDTH);
	printColor(makeArray("ACTION: ", 9), "white");
	printf("Find string with");
	printf("\n");
	printCenterSpaces(10, WIDTH);
	printf("the maximum matching letters.");
	printf("\n");
}

void printSimpleTableHeader()
{
	printNtimes('-', WIDTH);
	printf("\n");
	printColor(makeArray("ROW", 3), "magenta");
	printf(" | ");
	printNtimes(' ', (WIDTH - 40) / 2);
	printColor(makeArray("SHIFTED STRING", 14), "blue");
	printNtimes(' ', (WIDTH - 40) / 2);
	printf(" | ");
	printColor(makeArray("MATCHING LETTERS", 16), "green");
	printf("\n");
	printNtimes('-', WIDTH);
	printf("\n");
}

void printSimpleRow(int row, array shifted_string, int matching_letters)
{
	setColor("magenta");
	printf("%02i ", row);
	resetColor();
	printf(" | ");
	setColor("blue");
	printArray(shifted_string);
	resetColor();
	printf(" | ");
	setColor("green");
	printf("%2i\n", matching_letters);
	resetColor();
}

void printAdvancedHeader(array encoded, array decoded)
{
	printNtimes('*', WIDTH);
	printf("\n\n");
	setColor("white");
	printCenterSpaces(21, WIDTH);
	printf("ADVANCED DECODING LOG\n\n");
	resetColor();
	printNtimes(' ', 1);
	printColor(makeArray("SETTINGS:", 10), "yellow");
	resetColor();
	printf("\n");
	setColor("white");
	printf("ENCODED MESSAGE:");
	resetColor();
	printf("\n");
	printArray(encoded);
	printf("\n");
	setColor("white");
	printf("PARTLY DECODED MESSAGE:");
	printf("\n");
	resetColor();
	printArray(decoded);
	printf("\n\n");
	printNtimes('-', WIDTH);
	printf("\n");
	printCenterSpaces(26, WIDTH);
	printColor(makeArray("ACTION: ", 9), "white");
	printf("Find string with the lowest");
	printf("\n");
	printCenterSpaces(10, WIDTH);
	printf("Levenshtein distance.");
	printf("\n");
}

void printAdvancedTableHeader()
{
	printNtimes('-', WIDTH);
	printf("\n");
	printColor(makeArray("ROW", 3), "magenta");
	printf(" | ");
	printNtimes(' ', (WIDTH - 64) / 2);
	printColor(makeArray("SHIFTED STRING", 14), "blue");
	printNtimes(' ', (WIDTH - 64) / 2);
	printf(" |  ");
	printColor(makeArray("MATCHING LETTERS", 16), "green");
	printf(" | ");
	printColor(makeArray("LEVENSHTEIN DISTANCE", 16), "cyan");
	printf("\n");
	printNtimes('-', WIDTH);
	printf("\n");
}

void printAdvancedRow(int row, array shifted_string, int matching_letters, int levenshtein_distance)
{
	setColor("magenta");
	printf("%02i ", row);
	resetColor();
	printf(" | ");
	setColor("blue");
	printArray(shifted_string);
	resetColor();
	printf(" | ");
	setColor("green");
	printf("%2i", matching_letters);
	resetColor();
	printf(" | ");
	setColor("cyan");
	printf("%2i\n", levenshtein_distance);
	resetColor();
}

void printResultHeader(void)
{
	resetColor();
	printf("\n");
	setColor("red");
	printCenterSpaces(16, WIDTH);
	printf("RESULT OF ACTION");
	printf("\n");
	resetColor();
}

void printResult(array encoded, array decoded, int exit_code)
{
	printf("\n");
	printNtimes('-', WIDTH);
	printf("\n");
	printCenterSpaces(16, WIDTH);
	printColor(makeArray("RESULT OF PROGRAM", 17), "yellow");
	printf("\n");
	printNtimes(' ', 2);
	printColor(makeArray("ENCODED MESSAGE", 15), "white");
	printf("\n");
	printArray(encoded);
	printf("\n");
	printNtimes(' ', 2);
	printColor(makeArray("DECODED MESSAGE", 15), "white");
	printf("\n");
	printArray(decoded);
	printf("\n");
	printColor(makeArray("PROGRAM FINISHED WITH EXIT CODE ",32),"blue");
	setColor("cyan");
	printf("%i\n", exit_code);
	resetColor();
	printNtimes('*', WIDTH);
	printf("\n");

}

#endif
