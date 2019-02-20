#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <limits.h>

#define ERROR INT_MIN

//Function to allocate data for graph
graph_t* allocate_graph()
{
    graph_t* reti = (graph_t*)malloc(sizeof(graph_t));
    reti->length = 0;
    reti->capacity = 0;
    return reti;
}

//Function to free graph
void free_graph(graph_t **graph)
{
    graph_t* g = *graph;
    free(g->nodes);
    free(g);
}

//Function to add node data to graph
void add_node(int start, int finish, int cost, graph_t* graph)
{
    if (graph->capacity == 0)
    {
        graph->nodes = (node_t*)malloc(2 * sizeof(node_t));
        graph->capacity = 2;
    }
    else if ((graph->length + 1) > graph->capacity)
    {
        node_t* nodes = realloc(graph->nodes, (2 * graph->capacity * sizeof(node_t)));
        graph->nodes = nodes;
        graph->capacity = 2 * graph->capacity;
    }
    graph->nodes[graph->length].start = start;
    graph->nodes[graph->length].finish = finish;
    graph->nodes[graph->length].cost = cost;
    graph->length++;
}

//Function to check if char is number
int is_number(int c)
{
    int reti = ERROR;

    if (c >= '0')
    {
        if (c <= '9')
        {
            reti = 0;
        }
    }
    return reti;
}

//Function to load int from binary file
int load_int(FILE *fp)
{
    int reti = 0;
    char loaded = 0;
    int c;
    do
    {
        c = fgetc(fp);
        if (is_number(c) == 0)
        {
            reti *= 10;
            reti += (c - '0');
            loaded = 1;
        }
        else
        {
            reti = (loaded == 0) ? ERROR : reti;
            break;
        }


    }
    while (c != ' ' && c != '\n');

    return reti;
}

//Function to load data from txt faster than naive
void load_txt_fast(const char *fname, graph_t *graph)
{
    int pointA = 0;
    int pointB = 0;
    int value = 0;
    FILE *fp = fopen(fname, "r");
    do
    {
        pointA = load_int(fp);
        pointB = load_int(fp);
        value = load_int(fp);
        if (pointA != ERROR && pointB != ERROR && value != ERROR)
        {
            add_node(pointA, pointB, value, graph);
        }
    }
    while (pointA != ERROR && pointB != ERROR && value != ERROR);
    fclose(fp);
}

//Function to naive loading data from txt (using fscanf)
void load_txt_naive(const char *fname, graph_t *graph)
{
    FILE * fp;
    fp = fopen(fname, "r");
    int pointA, pointB, value;
    while(fscanf(fp, "%i %i %i", &pointA, &pointB, &value) == 3)
    {
        add_node(pointA, pointB, value, graph);
    }
    fclose(fp);
}

//Function to load graph data from text file
void load_txt(const char *fname, graph_t *graph)
{
    //load_txt_naive(fname, graph);
    load_txt_fast(fname, graph);
}


//Function to naive saving graph data to text file (using fprintf)
void save_txt_naive(const graph_t* const graph, const char* fname)
{
    FILE * fp;
    fp = fopen(fname, "w");
    for (int i = 0; i < graph->length; i++)
    {
        fprintf(fp, "%i %i %i\n", graph->nodes[i].start, graph->nodes[i].finish, graph->nodes[i].cost);
    }
    fclose(fp);
}



//Function to write int to file
void write_int(FILE* fp, int number)
{
    int dividers[] = {1000000000,100000000,10000000,1000000,100000,10000,1000,100,10,1};
    //1000000000 because there isn't greater 10^n divider for int
    int remain = number;
    char before = 0;
    for (int i = 0; i < (sizeof(dividers) / sizeof(int)); i++)
    {
        int integer = remain / dividers[i];
        if (integer > 0)
        {
            fputc(('0' + integer), fp);
            before = 1;
        }
        else if (before == 1)
        {
            fputc(('0' + integer), fp);
        }
        else if (i == ((sizeof(dividers) / sizeof(int)) - 1))
        {
            fputc(('0' + integer), fp);
        }

        remain = remain - (integer * dividers[i]);
    }
}

//Function to faster saving graph data to text file
//EDIT: It's even slower than fprintf!
void save_txt_fast(const graph_t * const graph, const char *fname)
{
    FILE *fp = fopen(fname, "w");
    for (int i = 0; i < graph->length; i++)
    {
        write_int(fp, graph->nodes[i].start);
        fputc(' ', fp);
        write_int(fp, graph->nodes[i].finish);
        fputc(' ', fp);
        write_int(fp, graph->nodes[i].cost);
        fputc('\n', fp);
    }

    fclose(fp);
}

//Function to write int to file in binary way
void write_int_bin(int number, FILE* fp)
{
    int dividers[] = {1000000000,100000000,10000000,1000000,100000,10000,1000,100,10,1};
    //1000000000 because there isn't greater 10^n divider for int
    int remain = number;
    char before = 0;
    for (int i = 0; i < (sizeof(dividers) / sizeof(int)); i++)
    {
        int integer = remain / dividers[i];
        int write = ('0' + integer);
        if (integer > 0)
        {
            fwrite(&write, sizeof(int), 1, fp);
            before = 1;
        }
        else if (before == 1)
        {
            fwrite(&write, sizeof(int), 1, fp);
        }
        else if (i == ((sizeof(dividers) / sizeof(int)) - 1))
        {
            fwrite(&write, sizeof(int), 1, fp);
        }

        remain = remain - (integer * dividers[i]);
    }
}

//Function to save graph data to txt file using fwrite
//EDIT: It's even more slower, so i don't care anymore...
void save_txt_fwrite(const graph_t * const graph, const char *fname)
{
    FILE *fp = fopen(fname, "w");
    int space = ' ';
    int new_line = '\n';
    for (int i = 0; i < graph->length; i++)
    {
        write_int_bin(graph->nodes[i].start, fp);
        fwrite(&space, sizeof(int), 1, fp);
        write_int_bin(graph->nodes[i].finish, fp);
        fwrite(&space, sizeof(int), 1, fp);
        write_int_bin(graph->nodes[i].cost, fp);
        fwrite(&new_line, sizeof(int), 1, fp);
    }
    fclose(fp);
}

//Function to save graph data to text file
void save_txt(const graph_t * const graph, const char *fname)
{
    //save_txt_naive(graph, fname);
    save_txt_fast(graph, fname);
    //save_txt_fwrite(graph, fname);
}




//Function to save graph data to binary file
void save_bin(const graph_t * const graph, const char *fname)
{
    FILE *fp = fopen(fname, "w");
    for (int i = 0; i < graph->length; i++)
    {
        fwrite(&(graph->nodes[i].start), sizeof(int), 1, fp);
        fwrite(&(graph->nodes[i].finish), sizeof(int), 1, fp);
        fwrite(&(graph->nodes[i].cost), sizeof(int), 1, fp);
    }
    fclose(fp);

}

//Function to load graph data from binary file
void load_bin(const char *fname, graph_t *graph)
{
    FILE *fp = fopen(fname, "r");
    int loaded[3];
    int l = 0;
    do
    {
        l = fread(&loaded, sizeof(int), 3, fp);
        if (l == 3)
        {
            add_node(loaded[0], loaded[1], loaded[2], graph);
        }

    }
    while (l == 3);
    fclose(fp);
}
