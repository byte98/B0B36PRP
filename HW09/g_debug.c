//
// Created by skodaj on 2.12.18.
//

#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include <limits.h>

#define ERROR INT_MIN



//Struct to store info about graph node
struct Node
{
    int start;
    int finish;
    int cost;
};
typedef struct Node node_t;

typedef struct
{
    node_t* nodes;
    int length;
    int capacity;
} graph_t;

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

    //printf(BBLUE "[INFO] " BLUE " === Checking, if loaded char is number === \n       inspected char: " BCYAN "%i" CYAN" ('%c')" BLUE "\n       maximum: " BCYAN "%i" CYAN" ('%c')" BLUE "\n       minimum: " BCYAN "%i" CYAN" ('%c')\n" RST , c, c, '0', '0', '9', '9');
    //printf("       " BLUE "Result: ");
    if (c >= '0')
    {
        if (c <= '9')
        {
            reti = 0;
        }
    }
    /*if (reti == 0)
    {
        printf(BGREEN "TRUE");
    }
    else
    {
        printf(BRED "FALSE");
    }
    printf("\n");*/
    return reti;
}

//Function to load int from binary file
int load_int(FILE *fp)
{
    printf(BBLUE "[INFO] " RST BLUE "Loading int...\n");
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
            printf(BBLUE "[INFO] " RST BLUE "Loaded char: " RST BYELLOW "%c" RST YELLOW " (%i)" RST "\n", c, c);
            loaded = 1;
        }
        else
        {
            reti = (loaded == 0) ? ERROR : reti;
            printf(BBLUE "[INFO] " RST RED "Char " BRED "cannot" RST RED " be loaded as int! " RST BLUE "(not in range " RST BYELLOW "%i " RST YELLOW " ['0'] " RST BLUE "- " RST BYELLOW "%i" RST YELLOW " ['9']" RST BLUE")" RST "\n", '0', '9');
            break;
        }


    }
    while (c != ' ' && c != '\n');
    if (reti != ERROR)
    {
        printf(BBLUE "[INFO] " RST BLUE "INT " RST BGREEN "%i" RST GREEN " successfully " RST BLUE "loaded!\n", reti);
    }
    else
    {
        printf(BBLUE "[INFO] " BRED "ERROR " BLUE "returned!\n"RST);
    }

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
            printf(BBLUE "[INFO] " RST BLUE "Adding " RST BCYAN "node" RST "\n              " BCYAN " - start " RST CYAN "%i" RST "\n              " BCYAN " - finish " RST CYAN "%i" RST "\n              " BCYAN " - cost " RST CYAN "%i" RST "\n       " RST BLUE "to " CYAN "graph" RST CYAN ".\n" RST,
                   pointA, pointB, value);
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


//Function to save graph data to text file
void save_txt(const graph_t * const graph, const char *fname)
{
    //save_txt_naive(graph, fname);
    save_txt_fast(graph, fname);
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

//Prints info about graph
void print_info(graph_t *graph)
{
    printf("=== GRAPH INFO ===\n -length: %i\n -capacity: %i\n *** STORED DATA ***\n", graph->length, graph->capacity);
    for (int i = 0; i < graph->length; i++)
    {
        printf(" -[%i]: %i %i %i\n", i, graph->nodes[i].start, graph->nodes[i].finish, graph->nodes[i].cost);
    }
    printf("\n");


}

int main(int argc, char *argv[])
{
    graph_t* graph = allocate_graph();
    load_txt("test.txt", graph);
    save_txt(graph, "save.txt");
    //save_bin(graph, "save.bin");

    //graph_t* binary_graph = allocate_graph();
    //load_bin("save.bin", binary_graph);
    print_info(graph);
    //print_info(binary_graph);*/
    free_graph(&graph);
    //free_graph(&binary_graph);

    return 0;
}
