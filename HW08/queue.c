#include "queue.h"

// TODO - your code

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
void** makedata(int count)
{
    void** reti = malloc(count * sizeof(void*));
    for (int i = 0; i < count; i++)
    {
        reti[i] = (void *) NULL;
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
    reti->data = makedata(capacity);



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
    if(queue->length < queue->capacity)
    {
        queue->data[queue->push_index] = data;
        queue->length++;
        queue->push_index = (queue->push_index + 1) % queue->capacity;
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
