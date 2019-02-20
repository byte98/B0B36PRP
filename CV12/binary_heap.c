#include <stdio.h>
#include <limit.h>

#define DEL INT_MIN

//Function to compute left child of pareint with index
int getLChildIdx(int index);

//Function to compute right child of pareint with index
int getRChildIdx(int index);

//Function to compute index of parent of child with index
int getParentIdx(int index);

//Function to add item to heap
int insert(int* heap, int priority, int index);

//Function to propagate up item in heap to make heap heap again
void propagate_up(int* heap, int index);

//Function to print info about array
void print_array(int* array, int length);

//Function to delete maximum priority
int delete_max(int* heap, int length);

//Function to propagate down item (parent to childs)
void propagate_down(int* heap, int index, int length);

/* Main program */
int main(int argc, char *argv[])
{
	int reti = 0;
	int heap_len = 30; //Length of heap
	int insert_index = 0; // Index to insert
	int heap[heap_len];
	insert_index = insert(heap, 10, insert_index);
	insert_index = insert(heap, 20, insert_index);
	insert_index = insert(heap, 5, insert_index);
	insert_index = insert(heap, 50, insert_index);
	insert_index = insert(heap, 1, insert_index);
	print_array(heap, insert_index);


	return reti;
}

int getLChildIdx(int index)
{
	return ((2 * index) + 1);
}

int getRChildIx(int index)
{
	return ((2 * index) + 2);
}

int getParentIdx(int index)
{
	return (int)((index - 1) / 2);
}

int insert(int* heap, int priority, int index)
{
	heap[index] = priority;
	propagate_up(heap, index);

	return (index + 1);
}

void propagate_up(int* heap, int index)
{
	if (index >= 0)
	{
		int me = heap[index];
		int parent = heap[getParentIdx(index)];
		if (me > parent)
		{
			heap[getParentIdx(index)] = me;
			heap[index] = parent;
			propagate_up(heap, getParentIdx(index));
		}
	}
}

void print_array(int* array, int length)
{
	printf(" ===== ARRAY INFO =====\n");
	printf(" length: %i\n", length);
	printf(" --- Stored data ---\n");
	for (int i = 0; i < length; i++)
	{
		printf("  -[%i]: %i\n", i, array[i]);
	}
	printf("\n");
}

int delete_max(int* heap, int length)
{
	int first = heap[0];
	int last = heap[(length - 1)];
	heap[0] = last;
	propagate_down(heap,
		return (length - 1);
}

void propagate_down(int* heap, int index, int length)
{
	if (index < length)
	{
		int me = heap[index];
		int lchild = heap[getLChildIdx(index)];
		int rchild = heap[getRChildIdx(index)];
		//Have I got higher priority?
		if (me <

	}
}
