#include <stdio.h>
#include <string.h>

/*
 * Endianity:
 *  Describes the way, how is the integer saved to memory.
 *  Example: Number 125 (each cipher represents one byte; 1 is the most important, 5 is the smalles)
 *           Addresses: 0 1 2 3 4 5
 *          Big Endian: 1 2 5
 *       Little Endian: 5 2 1
 */

struct test
{
	int ival;
	char cval;
};
typedef struct test test_t;

struct test2
{
	int ival;
	char cval;
	char *str;
};
typedef struct test2 test2_t;


//Example of writnig numbers to binary file
void write_numbers_to_file();

//Example of loading numbers from binary file
void load_numbers_from_file();

//Example of writing struct to binary file
void write_test_struct_to_file();

//Example of loading struct from binary file
void load_struct_from_file();

//Example of writing second strcut to binary file
void write_test2_struct_to_file();

//Example of loading second strcut to binary file
void load_struct2_from_file(test2_t *t);

/* Main program */
int main(int argc, char *argv[])
{
	int reti = 0;

	write_numbers_to_file();
	load_numbers_from_file();

	write_test_struct_to_file();
	load_struct_from_file();

	write_test2_struct_to_file();
	test2_t t;
	load_struct2_from_file(&t);
	printf(" === LOADED STRUCT ===\n test_t some_struct:\n");
	printf("  - [int]  ival: %i\n  - [char] cval: %c\n  - [char] *str: %s", t.ival, t.cval, t.str);



	return reti;
}


void write_numbers_to_file()
{
	int nums[] = { 1, 2, 3, 4, 5 };
	FILE *fp = fopen("nums", "w");
	fwrite(nums, sizeof(*nums), sizeof(nums) / sizeof(*nums), fp);
	float floats[] = { 0.1, 0.2, 0.3, 0.4, 0.50 };
	fwrite(floats, sizeof(*floats), sizeof(floats) / sizeof(*floats), fp);
	fclose(fp);
}

void load_numbers_from_file()
{
	int nums[5];
	float floats[5];
	FILE *fp = fopen("nums", "r");
	fread(nums, sizeof(*nums), sizeof(nums) / sizeof(*nums), fp);
	fread(floats, sizeof(*floats), sizeof(floats) / sizeof(*floats), fp);
	fclose(fp);

	printf(" === LOADED INTEGERS === \n  ");

	for (int i = 0; i < 5; i++)
	{
		printf("%i ", nums[i]);
	}

	printf("\n\n === LOADED FLOATS === \n  ");
	for (int i = 0; i < 5; i++)
	{
		printf("%f ", floats[i]);
	}
	printf("\n\n");
}

void write_test_struct_to_file()
{
	test_t some_struct;
	some_struct.ival = 13;
	some_struct.cval = 'a';

	FILE *fp = fopen("struct", "w");
	fwrite(&some_struct, sizeof(some_struct), 1, fp);
	fclose(fp);
}

void load_struct_from_file()
{
	test_t some_struct;
	FILE *fp = fopen("struct", "r");
	fread(&some_struct, sizeof(some_struct), 1, fp);
	printf(" === LOADED STRUCT ===\n test_t some_struct:\n");
	printf("  - [int]  ival: %i\n  - [char] cval: %c\n", some_struct.ival, some_struct.cval);
	fclose(fp);
}

void write_test2_struct_to_file()
{
	test2_t some_struct;
	some_struct.ival = 13;
	some_struct.cval = 'a';
	some_struct.str = "test2";

	FILE *fp = fopen("struct2", "w");
	fwrite(&some_struct.ival, sizeof(some_struct.ival), 1, fp);
	fwrite(&some_struct.cval, sizeof(some_struct.cval), 1, fp);
	fwrite(some_struct.str, strlen(some_struct.str) + 1, 1, fp);
	fclose(fp);
}

void load_struct2_from_file(test2_t *t)
{
	int ival;
	char cval;
	char str[100];

	FILE *fp = fopen("struct2", "w");
	fread(ival, sizeof(ival), 1, fp);
	fread(cval, sizeof(cval), 1, fp);
	char buffer;
	int i = 0;
	while (fread(&buffer, 1, 1, fp))
	{
		if (buffer == '\0')
		{
			break;
		}
		str[i] = buffer;
		i++;

	}
	fclose(fp);

	t->ival = ival;
	t->cval = cval;
	t->str = str;
}


