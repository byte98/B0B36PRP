// d.h
// File with headers of structs and functions used
// in HW10 - finding shortest path in graph
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "colors.h"

#ifndef HW10_D_H
#define HW10_D_H

/* Definitions of "global" variables */
#define ERROR INT_MIN //Defines returned value if something gone wrong
#define INFINITY INT_MAX //Defines something like infinity

/* struct Edge
 * Stores information about graph edge
 *  -int from: Start of edge
 *  -int to: End of edge
 *  -int cost: Cost of path from start to end of edge
 */
struct Edge
{
    int from;
    int to;
    int cost;
};
typedef struct Edge edge_t;

/* struct Path
 * Stores information about path
 *  -int dest: Where is path leading to
 *  -int cost: Cost of this path
 */
struct Path
{
    int dest;
    int cost;
};
typedef struct Path path_t;

/* struct Successor
 * Structure to store information about successors in graph
 *  -int parent: Says number of predecessor
 *  -int count: How much of successors are there
 *  -int capacity: Capacity of array of information about successors (to be able to free them)
 *  -path_t* dests: Data about successors
 */
struct Successor
{
    int parent;
    int count;
    int capacity;
    path_t* dests;
};
typedef struct Successor succ_t;

/* struct ResultPath
 * Stores information about path from beginning
 *  -int id: Identifies node
 *  -int cost: Cost of path from beginning
 *  -int predecessor: Predecessor on path from beginning
 */
struct ResultPath
{
    int id;
    int cost;
    int predecessor;
};
typedef struct ResultPath res_path_t;

/* struct Heap
 * Stores information about heap
 *  -int count: Count of items in heap
 *  -int* order: Order of items in heap
 *  -res_path_t* data: Data to be associated with heap (not used in heap, but only to decide order in heap)
 *  -int capacity: Capacity of heap (to be able to free them);
 */
struct Heap
{
    int count;
    int* order;
    int* indexes;
    res_path_t* data;
    int capacity;
};
typedef struct Heap heap_t;

/* struct Dijkstra
 * Structure to store information about whole dijkstra problem
 *  - edge_t* edges: Array describing edges from input
 *  - int length: Count of nodes in graph
 *  - int capacity: Available space in memory for graph
 *  - heap_t heap: Heap associated with implementation of Dijkstra's algorithm
 *  - res_path_t* result: Data including paths from beginning after Dijkstra's algorithm run
 *  - int result_len: Length of array with result
 *  - int result_len: Capacity of array with result
 *  - int max_point: Maximal available point
 *  - succ_t* successors: Edges data formatted to group same start points
 */
struct Dijkstra
{
    edge_t* edges;
    int length;
    int capacity;
    heap_t* heap;
    res_path_t* result;
    int result_len;
    int result_capacity;
    int max_point;
    succ_t* successors;
};
typedef struct Dijkstra dijkstra_t;




/* void add_edge(int start, int finish, int cost, graph_t* graph)
 * Adds edge to graph and reallocates space for graph, if needed
 * @param start: Starting point of edge
 * @param finish: Ending point of edge
 * @param cost: Cost of path from starting point to ending point
 * @param graph: Graph, where will be new edge added to
 * @return: Nothing (void)
 */
void add_edge(int start, int finish, int cost, dijkstra_t* dijkstra);



/* int is_number(int c)
 * Function to check, if given character is digit
 * @param c: Integer value of character to be checked
 * @return: 0 if character is digit or defined ERROR value if is not
 */
int is_number(int c);

/* int load_int(FILE *fp)
 * Loads one integer value from file
 * @param fp: Pointer to opened file where will be integer loaded character
 *            by character
 * @return: Returns loaded integer, if it was possible, or defined ERROR value if not
 */
int load_int(FILE *fp);

/* void load_txt(const char* fname, graph_t* graph)
 * Loads graph data from txt file
 * @param fname: Pointer to chars which contains file name, to be loaded data from
 * @param graph: Space in memory to be data saved in
 * @return: Nothing (void)
 */
void load_txt(const char* fname, dijkstra_t* dijkstra);

/* void save_txt(const graph_t* const graph, const char* fname)
 * Saves graph data to text file
 * @param fname: Pointer to chars which contains file name, to be data saved to
 * @param graph: Pointer to space in memory, where is graph saved
 * @return: Nothing (void)
 */
void save_txt(const dijkstra_t* const dijkstra, const char* fname);

/* void print_heap(heap_t* heap)
 * Print information about heap
 * @param heap: Heap structure to print information about
 * @param max: Maximal index of available data
 * @return: Nothing (void)
 */
void print_heap(heap_t* heap, int max);

/* void print_result(dijkstra_t* dijkstra)
 * Prints content of result array
 * @param dijkstra: Structure which contains info about result
 * @return: Nothing (void)
 */
void print_result(dijkstra_t* dijkstra);

/* void print_dijkstra(dijkstra_t* dijkstra)
 * Print information about dijkstra
 * @param graph: Dijkstra structure to print information about
 * @return: Nothing (void)
 */
void print_dijkstra(dijkstra_t* dijkstra);

/* int get_parent_idx(int index)
 * Computes index of parent in heap
 * @param index: Index to compute parent of
 * @return: Computed index of parent
 */
int get_parent_idx(int index);

/* int get_lchild_idx(int index)
 * Computes index of left child of item in binary heap
 * @param index: Index to compute left child of
 * @return: Computed index of left child
 */
int get_lchild_idx(int index);

/* int get_rchild_idx(int index)
 * Computes index of right child of item in binary heap
 * @param index: Index to compute right child of
 * @return: Computed index of right child
 */
int get_rchild_idx(int index);

/*void swap_items (int index1, int index2, heap_t heap)
 * Swap items in heap
 * @param index1: First item to be swapped
 * @param index2: Second item to be swapped
 * @param heap: Heap where swap should be done
 * @return: Nothing (void)
 */
void swap_items (int index1, int index2, heap_t* heap);

/* void propagate_up (int index, heap_t heap)
 * Propagates point up through binary heap recursively
 * @param index: Pointer to memory where is stored information about point
 * @param heap: Pointer to memory block where is heap stored
 * @return: Nothing (void)
 */
void propagate_up (int index, heap_t* heap);

/* void propagate_down(int index, heap_t heap)
 * Same as propagate up, but going through heap from top
 * @param index: Pointer to memory where is stored information about point
 * @param heap: Pointer to memory block where is heap stored
 * @return: Nothing (void)
 */
void propagate_down(int index, heap_t* heap);

/* void add_to_heap(heap_t heap, int id, int cost, int predecessor)
 * Adds data to heap
 * @param heap: Pointer to array which stores data of heap
 * @param id: Identifier of point in graph
 * @param cost: Cost of path from beginning
 * @param predecessor: Predecessor on path from beginning
 * @return: Nothing (void)
 */
void add_to_heap(heap_t* heap, int id, int cost, int predecessor);

/* res_path_t get_from_heap(heap_t heap)
 * Gets item from heap with highest "priority"
 * @param heap: Heap where to get item
 * @return: Return the right item from heap
 */
//res_path_t get_from_heap(heap_t* heap); ??? Is it necessary ???

/* void make_heap(dijkstra_t* dijkstra, int label)
 * Makes heap from graph data
 * @param dijkstra: Pointer to struct which stores info about graph
 * @param label: Label of beginning point
 * @return: Nothing (void)
 */
void make_heap(dijkstra_t* dijkstra, int label);


/* void add_successor(succ_t* successors, int parent, int destination, int cost)
 * Adds successor to point in graph
 * @param successors: Pointer to struct which stores information about successors
 * @param parent: Parent to successor
 * @param destination: Destination of successor
 * @param cost: Cost of path to destination
 * @return: Nothing (void)
 */
void add_successor(succ_t* successors, int parent, int destination, int cost);

/* void load_successors(dijkstra_t* dijkstra)
 * Loads successors of each point in graph
 * @param dijkstra: Structure which stores information about graph
 * @return: Nothing (void)
 */
void load_successors(dijkstra_t* dijkstra);

/* void do_dijkstra(dijkstra_t* dijkstra)
 * Runs some implementation of dijkstra's algorithm
 * for finding shortest path in graph
 * @param dijkstra: Pointer to struct which stores info about graph
 * @return: Nothing (void)
 */
void do_dijkstra(dijkstra_t* dijkstra, int label);

/**********  NEXT LINES ARE FROM OFFICIAL TASK ASSIGNMENT ***********/
/*** Source: https://cw.fel.cvut.cz/wiki/courses/b0b36prp/hw/hw10 ***/
/*
 * Initialize structure for storing graph, solution, and eventual
 * variables for dijkstra algorithm
 *
 * return: point to the allocated structure; NULL on an error
 */
void* dijkstra_init(void);


/*
 * Load input graph (in text format) from the given file and store it
 * to the dijkstra structure previously created by dijkstra_init()
 *
 * return: true on success; false otherwise
 */
_Bool dijkstra_load_graph(const char *filename, void *dijkstra);


/*
 * Set the graph to the dijkstra structure instead of direct
 * loading the file as in dijkstra_load_graph() function.
 * The given array edges should not be directly used for the
 * internal representation of the graph in the dijkstra algorithm
 *
 * return: true on success; false on an error, e.g., memory allocation
 */
_Bool dijkstra_set_graph(int e, int edges[][3], void *dijkstra);


/*
 * Solve the dijsktra algorithm on the graph previously
 * loaded by the dijkstra_load_graph() set by dijkstra_set_graph()
 * The solution is stored in some internal structure of the dijkstra
 * type passed to the function
 *
 * return: true on success; false otherwise
 */
_Bool dijkstra_solve(void *dijkstra, int label);


/*
 * Retrived the solution found by the function dijkstra_solve()
 * It is assumed the passed argument solution[][3] is properly allocated,
 * and thus the internal solution of the dijkstra can used to fill the
 * solution[][3].
 *
 * return: true on success; false otherwise
 */
_Bool dijkstra_get_solution(const void *dijkstra, int n, int solution[][3]);


/*
 * Directly solve the solution found by the dijkstra_solve() in to the
 * file (in the text format) with the given filename.
 *
 * return: true on success; false otherwise
 */
_Bool dijkstra_save_path(const void *dijkstra, const char *filename);


/*
 * Release on allocated memory of the passed structure for
 * the dijkstra algorithm, e.g., graph as an array of pointers to struct edge
 * and solution as an array of pointers to struct node.
 * All previosly allocated memory related to solution of the shortest
 * paths is freed
 */
void dijkstra_free(void *dijkstra);

#endif //HW10_D_H
