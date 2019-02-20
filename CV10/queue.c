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

//Struct for queue
struct Queue
{
	int* data;
	int length;
	int capacity;
	int push_index;
	int pop_index;
};
typedef struct Queue queue_t;

//Function to create empty memory space for data
int* make_empty_data(int capacity);

//Function to prepare memory for queue
queue_t* create_queue(int capacity);

//Function to push number into queue
char push(queue_t* queue, int number);

//Function to pop number from queue
int pop(queue_t* queue);

//Function to delete queue
void delete_queue(queue_t* queue);

//Functoin to print info about queue
void print_queue_info(queue_t* queue);


/* Main program */
int main(int argc, char *argv[])
{
	int reti = 0;
	int capacity = 0;
	printf("Enter queue capacity [int]: ");
	if (scanf("%i", &capacity) == 1)
	{
		queue_t* queue = create_queue(capacity);
		char cmd = 0;
		printf("Enter command [char{'a'/'r'/'i'/'q'/'q'}] | ['a' int]:");
		while (scanf("%c", &cmd) == 1)
		{
			if (cmd == 'i')
			{
				print_queue_info(queue);
				printf("Enter command [char{'a'/'r'/'i'/'q'}] | ['a' int]:");
			}
			else if (cmd == 'a')
			{
				int number = 0;
				scanf("%i", &number);
				char p = push(queue, number);
				if (p == TRUE)
				{
					printf("Number"  GREEN  " succesfully "  RESET  " pushed into queue.\n");
				}
				else
				{
					printf("Number push"  RED  " FAILED "  RESET  "!\n");
				}
				printf("Enter command [char{'a'/'r'/'i'/'q'}] | ['a' int]:");
			}
			else if (cmd == 'r')
			{
				int p = pop(queue);
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
				delete_queue(queue);
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

queue_t* create_queue(int capacity)
{
	queue_t* reti = (queue_t*)malloc(sizeof(queue_t));
	reti->length = 0;
	reti->push_index = 0;
	reti->pop_index = 0;
	reti->capacity = capacity;
	reti->data = make_empty_data(reti->capacity);

	return reti;
}

char push(queue_t* queue, int number)
{
	char reti = FALSE;
	if (queue->length < queue->capacity)
	{
		reti = TRUE;
		queue->data[queue->push_index] = number;
		queue->push_index++;
		queue->length++;
	}

	return reti;
}

int pop(queue_t* queue)
{
	int reti = ERROR;

	if (queue->length > 0)
	{
		reti = queue->data[queue->pop_index];
		queue->data[queue->pop_index] = (int)NULL;
		queue->pop_index++;
		queue->length--;
	}

	return reti;
}

void delete_queue(queue_t* queue)
{
	free(queue->data);
	free(queue);
}

void print_queue_info(queue_t* queue)
{
	printf("========= QUEUE INFO =========\n");
	printf("  - capacity: %i\n  - length: %i\n  - push index: %i\n  - pop index: %i\n", queue->capacity, queue->length, queue->push_index, queue->pop_index);
	printf(" ***** STORED DATA *****\n");
	for (int i = 0; i < queue->capacity; i++)
	{
		printf("   -[%i]: %i\n", i, queue->data[i]);
	}
	printf("\n");
}
