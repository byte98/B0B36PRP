//
// Created by skodaj on 24.11.18.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// TODO - your code


typedef struct {
    // TODO - Include your data structure here
    int capacity;
    int length;
    int pop_index;
    int push_index;
    void** data;
} queue_t;



//Function to print some info about queue
void print_queue(queue_t* queue)
{
    printf("======= QUEUE INFO =======\n - capacity: %i\n - pop index: %i\n - push index: %i\n - length: %i\n --- STORED DATA ---\n", queue->capacity, queue->pop_index, queue->push_index, queue->length);
    for (int i = 0; i < queue->capacity; i++)
    {
        printf("   -[%i]: %i\n", i, (int)queue->data[i]);
    }

}

//Function to prepare memory space for queue data
void** make_empty_data(int count)
{
    void** reti = malloc(count * sizeof(void*));
    for (int i = 0; i < count; i++)
    {
        reti[i] = (void *) NULL;
    }

    return reti;
}

//Function to prepare memory for queue data from existing queue (with same indexing)
void** make_exists_data(int count, void**data, int length)
{
    void** reti = make_empty_data(count);
    int i = 0;
    for (; i < length; i++)
    {
        reti[i] = data[i];
    }
    return reti;
}

//Function to prepare memory for queue data from existing queue (with reindexing from 0)
void** make_exists_data_re(int count, void** data, int length, int start)
{
    void** reti = make_empty_data(count);
    for (int i = 0; i < length; i++)
    {
        reti[i] = data[(start + i)];
    }
    return reti;
}


queue_t* create_queue(int capacity)
{
    queue_t* reti = malloc(sizeof(queue_t));
    reti->capacity = capacity;
    reti->push_index = 0;
    reti->pop_index = 0;
    reti->length = 0;
    reti->data = make_empty_data(capacity);



    return reti;
}





void delete_queue(queue_t *queue)
{
    free(queue->data);
    free(queue);
}


bool push_to_queue(queue_t *queue, void *data)
{
    bool reti = false;
    if(queue->length < queue->capacity) //Data fits into capacity
    {
        queue->data[queue->push_index] = data;
        queue->length++;
        queue->push_index++;
        reti = true;
    }
    else
    {
        queue->capacity = (2 * queue->capacity); //Data doesn't fit
        void ** newdata = make_exists_data(queue->capacity, queue->data, queue->length);
        free(queue->data);
        queue->data = newdata;
        queue->data[queue->push_index] = data;
        queue->length++;
        queue->push_index++;
        reti = true;

    }

    return reti;
}

void* pop_from_queue(queue_t *queue)
{
    void* reti = NULL;
    if (queue->length > 0)
    {
        reti = queue->data[queue->pop_index];
        queue->data[queue->pop_index] = NULL;
        queue->pop_index = (queue->pop_index + 1) % queue->capacity;
        queue->length --;
    }

    //Check if can change capacity
    int limit = queue->capacity / 3;
    if (queue->length <= limit && limit > 0)
    {
        void** new_data = make_exists_data_re(limit, queue->data, queue->length, queue->pop_index);
        free(queue->data);
        queue->pop_index = 0;
        queue->capacity = limit;
        queue->data = new_data;
    }


    return reti;
}


void* get_from_queue(queue_t *queue, int idx)
{
    void* reti = NULL;
    if (queue->pop_index + idx < queue->push_index && idx >= 0)
    {
        reti = queue->data[queue->pop_index + idx];
    }
    return reti;
}


int get_queue_size(queue_t *queue)
{
    return queue->length;
}



int main(int argc, char* argv[])
{
    printf("Enter length of queue [int]:\n>_ ");
    int c = 0;
    scanf("%i", &c);
    queue_t* queue = create_queue(c);
    char cmd = 0;
    while(cmd != 'q')
    {
        printf("\n\nEnter command [char('a'/'r'/'g'/'l'/'i'/'q') | 'a'/'g' int]:\n>_ ");

        scanf(" %c", &cmd);

        if (cmd == 'a')
        {
            int value = 0;
            scanf(" %i", &value);
            printf("\nEntered command: Push value %i to queue\n", value);
            printf("Command return value: ");
            void *ptr = value;
            printf("%s\n\n", push_to_queue(queue, ptr) ? "true" : "false");
        }
        else if (cmd == 'r')
        {
            printf("\nEntered command: Pop value from queue\n");
            printf("Command return value: ");
            printf("%i \n\n", pop_from_queue(queue));
        }
        else if (cmd == 'g')
        {
            int index = 0;
            scanf(" %i", &index);
            printf("Entered command: Get value on index %i\n", index);
            printf("Command return value: ");
            printf("%i \n\n", get_from_queue(queue, index));
        }
        else if (cmd == 'l')
        {
            printf("\nEntered command: Get size of queue\n");
            printf("Command return value: %i\n\n", get_queue_size(queue));
        }
        else if (cmd == 'i')
        {
            printf("\nEntered command: Get information about queue\n");
            printf("Command return value:\n");
            print_queue(queue);
            printf("\n\n");
        }
    }

    delete_queue(queue);
}



