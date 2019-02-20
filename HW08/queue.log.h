
#include "queue.h"

#define GRY "\033[1;30m"
#define REDL   "\x1B[0;31m"
#define RED   "\x1B[1;31m"
#define GRN   "\x1B[1;32m"
#define YEL   "\x1B[1;33m"
#define BLU   "\x1B[1;34m"
#define MAG   "\x1B[1;35m"
#define CYN   "\x1B[1;36m"
#define WHT   "\x1B[1;37m"
#define GRND  "\x1B[0;32m"
#define RESET "\x1B[1;0m"

void printQueue(queue_t* input)
{
	printf(GRY "[LOG]: queue_t\n       ├─ head: %i\n       ├─ tail: %i\n       ├─ index: %i\n       ├─ length: %i\n       ├─ stored: %i\n       └─ data\n" RESET, input->head, input->tail, input->index, input->length, input->stored);
	int i = 0;
	for (i = 0; i < (input->length - 1); i++)
	{
		printf(GRY "          ├─ [%i]: %i\n" RESET, i, input->data[i]);
	}
	printf(GRY "          └─ [%i]: %i\n" RESET, i, input->data[i]);
}