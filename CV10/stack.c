#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Definitions of something like a bool
#define TRUE 1
#define FALSE 0

//Definition of error
#define ERROR INT_MIN

//Definitions of colors
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"


//Struct for stack
struct Stack
{
	int* data;
	int length;
	int capacity;
	int push_index;
	int pop_index;
};
typedef struct Stack stack_t;

//Function to create empty memory space for data
int* make_empty_data(int capacity);

//Function to prepare memory for stack
stack_t* create_stack(int capacity);

//Function to push number into stack
char push(stack_t* stack, int number);

//Function to pop number from stack
int pop(stack_t* stack);

//Function to delete stack
void delete_stack(stack_t* stack);

//Functoin to print info about stack
void print_stack_info(stack_t* stack);


/* Main program */
int main(int argc, char *argv[])
{
	int reti = 0;
	int capacity = 0;
	printf("Enter stack capacity [int]: ");
	if (scanf("%i", &capacity) == 1)
	{
		stack_t* stack = create_stack(capacity);
		char cmd = 0;
		printf("Enter command [char{'a'/'r'/'i'/'q'/'q'}] | ['a' int]:");
		while (scanf("%c", &cmd) == 1)
		{
			if (cmd == 'i')
			{
				print_stack_info(stack);
				printf("Enter command [char{'a'/'r'/'i'/'q'}] | ['a' int]:");
			}
			else if (cmd == 'a')
			{
				int number = 0;
				scanf("%i", &number);
				char p = push(stack, number);
				if (p == TRUE)
				{
					printf("Number"  GREEN  " succesfully "  RESET  " pushed into stack.\n");
				}
				else
				{
					printf("Number push"  RED  " FAILED "  RESET  "!\n");
				}
				printf("Enter command [char{'a'/'r'/'i'/'q'}] | ['a' int]:");
			}
			else if (cmd == 'r')
			{
				int p = pop(stack);
				if (p == ERROR)
				{
					printf(RED "%i\n" RESET, p);
				}
				else
				{
					printf("%i\n", p);
				}

				printf("Enter command [char{'a'/'r'/'i'/'q'}] | ['a' int]:");
			}
			else if (cmd == 'q')
			{
				printf(YELLOW  "Exiting program...\n"  RESET);
				delete_stack(stack);
				break;
			}


		}


	}

	return reti;
}

int* make_empty_data(int capacity)
{
	int* reti = (int*)malloc(capacity * sizeof(capacity));
	for (int i = 0; i < capacity; i++)
	{
		reti[i] = (int)NULL;
	}
	return reti;
}

stack_t* create_stack(int capacity)
{
	stack_t* reti = (stack_t*)malloc(sizeof(stack_t));
	reti->length = 0;
	reti->push_index = 0;
	reti->pop_index = 0;
	reti->capacity = capacity;
	reti->data = make_empty_data(reti->capacity);

	return reti;
}

char push(stack_t* stack, int number)
{
	char reti = FALSE;
	if (stack->length < stack->capacity)
	{
		reti = TRUE;
		stack->data[stack->push_index] = number;
		stack->pop_index = stack->push_index;
		stack->push_index++;
		stack->length++;
	}

	return reti;
}

int pop(stack_t* stack)
{
	int reti = ERROR;

	if (stack->length > 0)
	{
		reti = stack->data[stack->pop_index];
		stack->data[stack->pop_index] = (int)NULL;
		stack->pop_index--;
		stack->length--;
	}

	return reti;
}

void delete_stack(stack_t* stack)
{
	free(stack->data);
	free(stack);
}

void print_stack_info(stack_t* stack)
{
	printf("========= STACK INFO =========\n");
	printf("  - capacity: %i\n  - length: %i\n  - push index: %i\n  - pop index: %i\n", stack->capacity, stack->length, stack->push_index, stack->pop_index);
	printf(" ***** STORED DATA *****\n");
	for (int i = 0; i < stack->capacity; i++)
	{
		printf("   -[%i]: %i\n", i, stack->data[i]);
	}
	printf("\n");
}
