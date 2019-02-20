#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "dynamic.h"
#include "caesar.h"


//Main function
int main(int argc, char *argv[])
{
	array encoded = loadDynamicArray('\n');
	if (checkArray(encoded) == FALSE)
	{
		freeArray(encoded);
		fprintf(stderr, "Error: Chybny vstup!\n");
		return 100;
	}
	array decoded = loadDynamicArray('\n');
	if (checkArray(decoded) == FALSE)
	{
		freeArray(encoded);
		freeArray(decoded);
		fprintf(stderr, "Error: Chybny vstup!\n");
		return 100;
	}

	if (encoded.count != decoded.count && hasArgument(argv, argc, "-prp-optional") == FALSE)
	{
		freeArray(encoded);
		freeArray(decoded);
		fprintf(stderr, "Error: Chybna delka vstupu!\n");
		return 101;
	}


	if (hasArgument(argv, argc, "-prp-optional") == TRUE)
	{
		array decoded_message = decodeAdvanced(encoded, decoded, hasArgument(argv, argc, "-log"));
		if (hasArgument(argv, argc, "-log") == FALSE)
		{
			printArray(decoded_message);
		}
		freeArray(decoded_message);
	}
	else
	{
		array decoded_message = decodeSimple(encoded, decoded, hasArgument(argv, argc, "-log"));
		if (hasArgument(argv, argc, "-log") == FALSE)
		{
			printArray(decoded_message);
		}
		freeArray(decoded_message);
	}
	printf("\n");
	freeArray(encoded);
	freeArray(decoded);
	return 0;

}
