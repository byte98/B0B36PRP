// _d_h.c
// File which stores implementations of functions
// defined in d.h

#define DEBUG 1

//Function to print info
void print_info(char* file, int line, char* string)
{
    printf(BBLUE " [INFO " BLUE "%s:%c" BLUE "] %s\n", file, line, string);
}

//Function to add edge data to graph
void add_edge(int start, int finish, int cost, dijkstra_t* dijkstra)
{

    if (dijkstra->capacity == 0)
    {
        if (DEBUG)
        {
            printf(BBLUE "[INFO" BLUE " %s:%i" BBLUE "]" BLUE " Reallocating space for " BBLUE "dijkstra" BLUE" from " BCYAN "%i" BLUE " to " BCYAN "%i" RST "\n", __FILE__ ,__LINE__, dijkstra->capacity , 2);
        }
        dijkstra->edges = (edge_t*)malloc(2 * sizeof(edge_t));
        dijkstra->capacity = 2;
    }
    else if ((dijkstra->length + 1) > dijkstra->capacity)
    {
        if (DEBUG)
        {
            printf(BBLUE "[INFO" BLUE " %s:%i" BBLUE "]" BLUE " Reallocating space for " BBLUE "dijkstra" BLUE" from " BCYAN "%i" BLUE " to " BCYAN "%i" RST "\n", __FILE__ ,__LINE__, dijkstra->capacity , 2 * dijkstra->capacity);

        }
        dijkstra->edges  = realloc(dijkstra->edges, (2 * dijkstra->capacity * sizeof(edge_t)));
        dijkstra->capacity = 2 * dijkstra->capacity;
    }

    edge_t edge = {
            .from = start,
            .to = finish,
            .cost = cost
    };
    dijkstra->edges[dijkstra->length] = edge;

    if (dijkstra->max_point < start)
    {
        dijkstra->max_point = start;
    }
    if (dijkstra->max_point < finish)
    {
        dijkstra->max_point = finish;
    }

    dijkstra->length++;
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

//Function to load data from txt char by char
void load_txt(const char *fname, dijkstra_t *dijkstra)
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
            add_edge(pointA, pointB, value, dijkstra);
        }
    }
    while (pointA != ERROR && pointB != ERROR && value != ERROR);
    fclose(fp);
}

//Function to naive saving graph data to text file (using fprintf)
void save_txt(const dijkstra_t* const dijkstra, const char* fname)
{
    FILE * fp;
    fp = fopen(fname, "w");
    for (int i = 0; i < dijkstra->result_len; i++)
    {
        fprintf(fp, "%i %i %i\n", dijkstra->result[i].id, dijkstra->result[i].cost, dijkstra->result[i].predecessor);
    }
    fclose(fp);
}

//Print info about heap
void print_heap(heap_t* heap, int max)
{
    printf(BBLUE "[INFO" BLUE " %s:%i" BBLUE "]" BLUE " Printing information about " BMAGENTA "Heap" RST "\n", __FILE__ ,__LINE__);
    printf("   " MAGENTA "        count: " BMAGENTA "%2i" RST "\n", heap->count);
    printf("   " MAGENTA "     capacity: " BMAGENTA "%2i" RST "\n", heap->capacity);
    printf("   " MAGENTA "        order: ");
    for (int i = 0; i < max; i++)
    {
        if (i > 0)
        {
            printf(",");
        }
        if (i < heap->count)
        {
            printf(MAGENTA" "BMAGENTA"%2i"MAGENTA, heap->order[i]);
        }
        else
        {
            printf(MAGENTA" "MAGENTA"%2i"MAGENTA, heap->order[i]);
        }
    }
    printf(RST"\n");
    printf("   " MAGENTA "      indexes: ");
    for (int i = 0; i < max; i++)
    {
        if (i > 0)
        {
            printf(",");
        }
        if (i < heap->count)
        {
            printf(MAGENTA" "BMAGENTA"%2i"MAGENTA, heap->indexes[i]);
        }
        else
        {
            printf(MAGENTA" "MAGENTA"%2i"MAGENTA, heap->indexes[i]);
        }

    }
    printf(RST"\n");
    printf("   " MAGENTA "ordered items: ");
    printf(RST "\n");
    for (int i = 0; i < max;  i++)
    {
        printf("             " MAGENTA "[%2i]: "CYAN"      id: "BCYAN"%i"RST"\n", i, heap->data[heap->order[i]].id);
        printf("                "CYAN"       cost: "BCYAN"%i"RST"\n", heap->data[heap->order[i]].cost);
        printf("                "CYAN"predecessor: "BCYAN"%i"RST"\n", heap->data[heap->order[i]].predecessor);
    }
    printf(RST "\n");

}

//Print info about result
void print_result(dijkstra_t* dijkstra)
{
    printf(BBLUE "[INFO" BLUE " %s:%i" BBLUE "]" BLUE " Printing information about " BGREEN "Result" RST "\n", __FILE__ ,__LINE__);

}


//Print info about graph
void print_dijkstra(dijkstra_t* dijkstra)
{
    //Basic info
    printf(BBLUE "[INFO" BLUE " %s:%i" BBLUE "]" BLUE " Printing information about " BBLUE "dijkstra" RST "\n", __FILE__ ,__LINE__);
    printf("   " BLUE "    length: " BBLUE "%i" RST "\n", dijkstra->length);
    printf("   " BLUE "  capacity: " BBLUE "%i" RST "\n", dijkstra->capacity);
    printf("   " BLUE " max_point: " BBLUE "%i" RST "\n", dijkstra->max_point);

    //Loaded edges of graph
    printf("   " BBLUE "Edges: " BLUE "(format: " BBLUE "from" BLUE " -> " BBLUE "to" BLUE " @ " BBLUE "cost" BLUE ")" RST "\n");
    for (int i = 0; i < dijkstra->length; i++)
    {
        printf("     " BLUE "[%2i]: " BBLUE, i);
        if (dijkstra->edges[i].from == INFINITY)
        {
            printf(BYELLOW "(INF)" BBLUE);
        }
        else if (dijkstra->edges[i].from == ERROR)
        {
            printf(BRED "(ERR)" BBLUE);
        }
        else
        {
            printf("%2i", dijkstra->edges[i].from);
        }
        printf(BLUE " -> " BBLUE);
        if (dijkstra->edges[i].to == INFINITY)
        {
            printf("(INF)");
        }
        else if (dijkstra->edges[i].to == ERROR)
        {
            printf(BRED "(ERR)" BBLUE);
        }
        else
        {
            printf("%2i", dijkstra->edges[i].to);
        }
        printf(BLUE " @ " BBLUE);
        if (dijkstra->edges[i].cost == INFINITY)
        {
            printf("(INF)");
        }
        else if (dijkstra->edges[i].cost == ERROR)
        {
            printf(BRED "(ERR)" BBLUE);
        }
        else
        {
            printf("%2i", dijkstra->edges[i].cost);
        }
        printf(RST "\n");

    }

    //Successors data
    printf("   " BBLUE "Successors: " RST "\n");
    for (int i = 0; i <= dijkstra->max_point; i++)
    {
        printf("     " BLUE "[%2i]: parent:   " BBLUE "%2i" RST "\n           " BLUE "count:    " BBLUE "%2i" RST "\n           " BLUE "capacity: " BBLUE "%2i" RST "\n", i, dijkstra->successors[i].parent, dijkstra->successors[i].count, dijkstra->successors[i].capacity);
        printf("           " CYAN "Destinations:\n");
        for (int c = 0; c < dijkstra->successors[i].count; c++)
        {
            printf( "             " CYAN " ↳ " BCYAN "%2i" CYAN " @ " BCYAN "%2i" RST "\n",  dijkstra->successors[i].dests[c].dest, dijkstra->successors[i].dests[c].cost);
        }
        printf(RST);
    }

    //Heap data
    printf("   " BBLUE "Heap: " RST "\n");
    for (int i = 0; i < (dijkstra->max_point + 1); i++)
    {
        printf("     " BLUE "[%2i]: " BBLUE, i);
        printf( BBLUE "%2i" RST, dijkstra->heap->order[i]);
        printf("\n     " YELLOW "     number: " BYELLOW "%2i" RST, dijkstra->heap->data[dijkstra->heap->order[i]].id);
        printf("\n     " YELLOW "       cost: ");
        if (dijkstra->heap->data[dijkstra->heap->order[i]].cost == INFINITY)
        {
            printf(BCYAN"(INF)");
        }
        else if(dijkstra->heap->data[dijkstra->heap->order[i]].cost == ERROR)
        {
            printf(BRED"(ERR)");
        }
        else
        {
            printf(BYELLOW "%2i", dijkstra->heap->data[dijkstra->heap->order[i]].cost);
        }
        printf(RST"\n     " YELLOW "predecessor: " BYELLOW "%2i" RST, dijkstra->heap->data[dijkstra->heap->order[i]].predecessor);
        printf(RST "\n");
    }

    //Result
    printf("   "BGREEN "Result:" RST "\n");
    for (int i = 0; i < dijkstra->result_len; i++)
    {
        printf("         " GREEN "[%2i]: " BGREEN "%2i" GREEN " @ " BGREEN "%2i" GREEN " via " BGREEN "%2i" RST "\n", i, dijkstra->result[i].id, dijkstra->result[i].cost, dijkstra->result[i].predecessor);
    }

    printf(RST "\n");
}

//Get index of parent in heap
int get_parent_idx(int index)
{
    return ((index - 1) / 2);
}

//Get index of left child in heap
int get_lchild_idx(int index)
{
    return ((2 * index) + 1);
}

//Get index of right child in heap
int get_rchild_idx(int index)
{
    return ((2 * index) + 2);
}

//Swap items in heap
void swap_items (int index1, int index2, heap_t* heap)
{
    if(DEBUG)
    {
        printf(BBLUE"[INFO"BLUE" %s:%i"BBLUE"]"BLUE" Items swap: Inputs " BBLUE "%i" BLUE" and " BBLUE"%i"RST"\n",
                __FILE__, __LINE__, index1, index2);
        printf(BBLUE"[INFO"BLUE" %s:%i"BBLUE"]"BLUE" Swapping items " BBLUE "%i" BLUE" and " BBLUE"%i"RST"\n",
                __FILE__, __LINE__, heap->order[index1], heap->order[index2]);
    }


    /*int cache = heap->order[index2];

    heap->indexes[heap->order[index1]] = index1;
    heap->indexes[heap->order[index2]] = index2;

    heap->order[index2] = heap->order[index1];
    heap->order[index1] = cache;*/

    int cache = heap->order[index2];
    heap->order[index2] = heap->order[index1];
    heap->order[index1] = cache;


}

//Propagate item up in binary heap to make heap heap again
void propagate_up (int index, heap_t* heap)
{
    if (index > 0)
    {
        if (heap->data[heap->order[index]].cost < heap->data[heap->order[get_parent_idx(index)]].cost)
        {
            swap_items(index, get_parent_idx(index), heap);
            propagate_up(get_parent_idx(index), heap);
        }
    }
}

//Same as propagate up, but obviously in opposite direction
void propagate_down(int index, heap_t* heap)
{
    if (index < heap->count)
    {
        if (heap->data[heap->order[index]].cost > heap->data[heap->order[get_lchild_idx(index)]].cost)
        {
            swap_items(index, get_lchild_idx(index), heap);
        }
        else if (heap->data[heap->order[index]].cost > heap->data[heap->order[get_rchild_idx(index)]].cost)
        {
            swap_items(index, get_rchild_idx(index), heap);
        }
    }
}

//Adds element to heap
void add_to_heap(heap_t* heap, int id, int cost, int predecessor)
{
    if (DEBUG)
    {
        printf(BBLUE "[INFO" BLUE " %s:%i" BBLUE "]" BLUE " Adding "
        BCYAN "item" CYAN "(id: " BCYAN "%i" CYAN", cost: " BCYAN "%i" CYAN ", predecessor: " BCYAN "%i" CYAN ")"
        BLUE " into " BBLUE "Heap" RST "\n", __FILE__, __LINE__, id, cost, predecessor);
    }

    res_path_t item = {
            .id = id,
            .cost = cost,
            .predecessor = predecessor
    };
    if (heap->capacity == 0)
    {
        heap->capacity = 2;
        heap->order = (int*)malloc(2 * sizeof(int));
        heap->indexes = (int*)malloc(2 * sizeof(int));
        heap->data = (res_path_t*)malloc(2 * sizeof(res_path_t));
    }
    else if (heap->count + 1 > heap->capacity)
    {
        heap->capacity = 2 * heap->capacity;
        heap->order = realloc(heap->order, heap->capacity * sizeof(int));
        heap->indexes = realloc(heap->order, heap->capacity * sizeof(int));
        heap->data = realloc(heap->data, heap->capacity * sizeof(res_path_t));
    }
    heap->data[heap->count] = item;
    heap->order[heap->count] = heap->count;
    heap->indexes[id] = heap->count;
    heap->count++;
    propagate_up(heap->count -1 , heap);

}

//Make heap from graph data
void make_heap(dijkstra_t* dijkstra, int label)
{
    dijkstra->heap = (heap_t*)malloc(sizeof(heap_t));
    dijkstra->heap->capacity = 0;
    dijkstra->heap->count = 0;
    for (int i = 0; i <= dijkstra->max_point; i++)
    {
        add_to_heap(dijkstra->heap, i, (i == label ? 0 : INFINITY), -1);
    }
}

//Add successor of point in graph
void add_successor(succ_t* successors, int parent, int destination, int cost)
{
    if (successors[parent].capacity == 0)
    {
        successors[parent].capacity = 2;
        if (DEBUG)
        {
            printf(BBLUE"[INFO"BLUE" %s:%i"BBLUE"]" BLUE" Reallocating capacity for "BBLUE"successors"BLUE" of " BYELLOW"%i"BLUE" from " BCYAN "%i" BLUE" to " BCYAN"%i" RST "\n",
                    __FILE__, __LINE__, parent, 0, successors[parent].capacity);
        }

        successors[parent].dests = (path_t*)malloc(successors->capacity * sizeof(path_t));
    }
    else if(successors[parent].count + 1 > successors[parent].capacity)
    {
        if (DEBUG)
        {
            printf(BBLUE"[INFO"BLUE" %s:%i"BBLUE"]" BLUE" Reallocating capacity for "BBLUE"successors"BLUE" of " BYELLOW"%i"BLUE" from " BCYAN "%i" BLUE" to " BCYAN"%i" RST "\n",
                    __FILE__, __LINE__, parent, successors[parent].capacity, 2 * successors[parent].capacity);

        }
        successors[parent].capacity = 2 * successors[parent].capacity;
        successors[parent].dests = realloc(successors[parent].dests, successors[parent].capacity* sizeof(path_t));
    }


    successors[parent].dests[successors[parent].count].dest = destination;
    successors[parent].dests[successors[parent].count].cost = cost;

    successors[parent].parent = parent;
    if (DEBUG)
    {
        printf(BBLUE"[INFO"BLUE" %s:%i"BBLUE"]"BLUE" Found successor of "BBLUE"%i"BLUE" (-> "BCYAN"%i" BLUE" @ " BCYAN"%i"BLUE")"RST"\n",
                __FILE__, __LINE__, successors[parent].parent, successors[parent].dests[successors[parent].count].dest, successors[parent].dests[successors[parent].count].cost);

    }

    successors[parent].count++;
}

//Load successors of all points in graph
void load_successors(dijkstra_t* dijkstra)
{
    dijkstra->successors = (succ_t*)malloc((dijkstra->max_point + 1) * sizeof(succ_t));
    for (int i = 0; i < dijkstra->length; i++)
    {
        dijkstra->successors[dijkstra->edges[i].from].capacity = 0;
        dijkstra->successors[dijkstra->edges[i].from].count = 0;
    }
    for (int i = 0; i < dijkstra->length; i++)
    {
        add_successor(dijkstra->successors, dijkstra->edges[i].from, dijkstra->edges[i].to, dijkstra->edges[i].cost);
    }
}

//Some implementation of Dijkstra's algorithm
void do_dijkstra(dijkstra_t* dijkstra, int label)
{
    /*
    dijkstra->result = (res_path_t*)malloc((dijkstra->max_point + 1) * sizeof(res_path_t));
    for (int i = 0; i <= dijkstra->max_point; i++)
    {
        res_path_t item = {
                .id = i,
                .cost = INFINITY,
                .predecessor = -1
        };
        dijkstra->result[i] = item;
        dijkstra->result_len++;
    }
    dijkstra->result_capacity = dijkstra->max_point + 1;
    while (dijkstra->heap->count > 0)
    {
        int index = dijkstra->heap->data[dijkstra->heap->order[0]].id;
        dijkstra->result[index] = dijkstra->heap->data[dijkstra->heap->order[0]];
        dijkstra->heap->count--;
        swap_items(0, (dijkstra->heap->count + 1), dijkstra->heap);
        propagate_down(0, dijkstra->heap);

        for (int i = 0; i < dijkstra->successors[index].count; i++)
        {
            int found_cost = dijkstra->result[dijkstra->successors[index].dests[i].dest].cost;
            int new_cost = dijkstra->result[index].cost + dijkstra->successors[index].dests[i].cost;
            if (new_cost < found_cost)
            {
                printf(BBLUE "[INFO" BLUE " %s:%i" BBLUE "]" BLUE" Found " BGREEN "\"cheaper\"" BLUE " path to " BYELLOW "%i" BLUE " (old: " BCYAN "%i" BLUE ", new: " BCYAN "%i" BLUE ")" RST "\n",
                        __FILE__, __LINE__, dijkstra->successors[index].dests[i].dest, found_cost, new_cost);
                dijkstra->result[dijkstra->successors[index].dests[i].dest].cost = new_cost;
                dijkstra->result[dijkstra->successors[index].dests[i].dest].predecessor = index;

                dijkstra->heap->data[dijkstra->heap->indexes[dijkstra->successors[index].dests[i].dest]].cost = new_cost;
                dijkstra->heap->data[dijkstra->heap->indexes[dijkstra->successors[index].dests[i].dest]].predecessor = index;
            }
        }
    }*/
    if (DEBUG)
    {
        printf(BBLUE"[INFO" BLUE" %s:%i" BBLUE"]"BLUE" Starting Dijkstra's algorithm..." RST "\n", __FILE__, __LINE__);
        print_heap(dijkstra->heap, (dijkstra->max_point + 1));

    }
    dijkstra->result = (res_path_t*)malloc((dijkstra->max_point + 1) * sizeof(res_path_t));
    for (int i = 0; i <= dijkstra->max_point; i++)
    {
        res_path_t item = {
                .id = i,
                .cost = INFINITY,
                .predecessor = -1
        };
        dijkstra->result[i] = item;
        dijkstra->result_len++;
    }
    dijkstra->result_capacity = dijkstra->max_point + 1;
    int count = 0;
    int checked[(dijkstra->max_point + 1)];
    for (int i = 0; i <= dijkstra->max_point; i++)
    {
        checked[i] = 0;
    }
    while(dijkstra->heap->count > 0)
    {


        //print_heap(dijkstra->heap, dijkstra->heap->count);

        //Get item with shortest found path and say that its path is definitive
        res_path_t node = dijkstra->heap->data[dijkstra->heap->order[0]];
        dijkstra->result[dijkstra->heap->order[0]] = node;

        checked[node.id]++;

        //Check successors if there is cheapest path from me
        for (int i = 0; i < dijkstra->successors[node.id].count; i++)
        {
            if (DEBUG)
            {
                printf(BBLUE"[INFO"BLUE" %s:%i"BBLUE"]"BLUE" Checking "BBLUE"successor"BLUE" of "BYELLOW"%i"BLUE": "BCYAN"%i"BLUE" "MAGENTA"("BMAGENTA"%i"MAGENTA"/"BMAGENTA"%i"MAGENTA")"RST"\n",
                        __FILE__, __LINE__, node.id, dijkstra->successors[node.id].dests[i].dest, (i + 1) ,dijkstra->successors[node.id].count);
                //printf(BBLUE"[INFO" BLUE" %s:%i" BBLUE"]"BLUE" Found "BGREEN"\"cheaper\"" BLUE" path to "BBLUE "%i" BLUE" (via "BCYAN"%i"BLUE" @ "BCYAN"%i" BLUE")"RST"\n",
                //        __FILE__, __LINE__, dijkstra->successors[node.id].dests[i].dest, node.id, dijkstra->successors[node.id].dests[i].cost);

            }
            count++;
            int found_price = dijkstra->result[node.id].cost + dijkstra->successors[node.id].dests[i].cost;
            int old_price = dijkstra->result[dijkstra->successors[node.id].dests[i].dest].cost;
            if (dijkstra->result[node.id].cost == INFINITY)
            {
                found_price = INFINITY;
            }



            //Found better price or none price
            if (found_price < old_price || dijkstra->result[dijkstra->successors[node.id].dests[i].dest].cost == INFINITY)
            {
                if (DEBUG)
                {
                    printf(BBLUE"[INFO" BLUE" %s:%i" BBLUE"]"BLUE" Found "BGREEN"\"cheaper\"" BLUE" path to "BBLUE "%i" BLUE" (via "BCYAN"%i"BLUE" @ "BCYAN"%i" BLUE")"RST"\n",
                            __FILE__, __LINE__, dijkstra->successors[node.id].dests[i].dest, node.id, found_price);

                }
                dijkstra->result[dijkstra->successors[node.id].dests[i].dest].cost = found_price;
                dijkstra->result[dijkstra->successors[node.id].dests[i].dest].predecessor = node.id;

                dijkstra->heap->data[dijkstra->successors[node.id].dests[i].dest].cost = found_price;
                dijkstra->heap->data[dijkstra->successors[node.id].dests[i].dest].predecessor = node.id;
                if (dijkstra->heap->indexes[dijkstra->successors[node.id].dests[i].dest] < dijkstra->heap->count)
                {
                    propagate_up(dijkstra->heap->indexes[dijkstra->successors[node.id].dests[i].dest],dijkstra->heap);
                }

                if (DEBUG)
                {
                    print_heap(dijkstra->heap, dijkstra->max_point + 1);

                }
            }
        }




        //print_heap(dijkstra->heap, dijkstra->max_point + 1);
        //print_result(dijkstra);

        //Remove item from heap
        swap_items(0, (dijkstra->heap->count - 1), dijkstra->heap);
        dijkstra->heap->count--;
        propagate_down(0, dijkstra->heap);


    }

    for (int i = 0 ; i <= dijkstra->max_point; i++ )
    {
        if (checked[i] == 0)
        {
            for (int s = 0; s < dijkstra->successors[i].count; s++)
            {
                int found_price = dijkstra->result[i].cost + dijkstra->successors[i].dests[s].cost;
                int old_price = dijkstra->result[dijkstra->successors[i].dests[s].dest].cost;
                if (dijkstra->result[i].cost == INFINITY)
                {
                    found_price = INFINITY;
                }
                if (found_price < old_price)
                {
                    dijkstra->result[dijkstra->successors[i].dests[s].dest].cost = found_price;
                    dijkstra->result[dijkstra->successors[i].dests[s].dest].predecessor = i;

                    dijkstra->heap->data[dijkstra->successors[i].dests[s].dest].cost = found_price;
                    dijkstra->heap->data[dijkstra->successors[i].dests[s].dest].predecessor = i;
                }
            }
        }
    }

    if (count < dijkstra->length && DEBUG)
    {
        printf(BYELLOW"[WARNING "YELLOW" %s:%i"BYELLOW"]"YELLOW" Not all "BYELLOW"edges"YELLOW" were checked (only "BYELLOW"%i"YELLOW"/"BYELLOW"%i"YELLOW")"RST"\n",
                __FILE__, __LINE__, count, dijkstra->length);
    }
    if (DEBUG)
    {
        printf(BBLUE"[INFO"BLUE" %s:%i"BBLUE"]"BLUE" Checked items:"RST"\n   "BLUE"  Items: " RST, __FILE__, __LINE__);
        for (int i = 0; i <= dijkstra->max_point; i++)
        {
            printf(BBLUE"%3i  ", i);
        }
        printf(RST"\n   "BLUE"Checked: "RST);
        for (int i = 0; i <= dijkstra->max_point; i++)
        {
            if (checked[i] < 1)
            {
                printf(BRED"%3i×"RST" ", checked[i]);
            }
            else if (checked[i] == 1)
            {
                printf(BGREEN"%3i×"RST" ", checked[i]);
            }
            else
            {
                printf(BYELLOW"%3i×"RST" ", checked[i]);
            }
            printf(RST);
        }
        printf(RST"\n");

        for (int i = 0; i < dijkstra->result_len; i++)
        {
            if (dijkstra->result[i].cost == INFINITY)
            {
                dijkstra->result[i].cost = -1;
            }
        }
    }


}

/*** And there starts official task assignment ***/
//Init Dijkstra struct
void* dijkstra_init(void)
{
    dijkstra_t* reti = (dijkstra_t*)malloc(sizeof(dijkstra_t));
    reti->length = 0;
    reti->capacity = 0;
    reti->result_len = 0;
    reti->max_point = 0;
    return reti;
}

//Load graph from txt and save it to struct
_Bool dijkstra_load_graph(const char *filename, void *dijkstra)
{
    _Bool reti = true;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        reti = false;
    }
    fclose(fp);
    load_txt(filename, dijkstra);
    load_successors(dijkstra);
    return reti;
}

//Set graph directly to struct
_Bool dijkstra_set_graph(int e, int edges[][3], void *dijkstra)
{
    _Bool reti = true;
    dijkstra_t *d = dijkstra;
    for (int i = 0; i < e; i++)
    {
        add_edge(edges[i][0], edges[i][1], edges[i][2], d);
    }
    load_successors(dijkstra);


    return reti;
}

//Solve actual problem
_Bool dijkstra_solve(void *dijkstra, int label)
{
    make_heap(dijkstra, label);
    //print_dijkstra(dijkstra);
    do_dijkstra(dijkstra, label);
    if (DEBUG)
    {
        print_dijkstra(dijkstra);
    }



    return true;
}

//Save solution to array
_Bool dijkstra_get_solution(const void *dijkstra, int n, int solution[][3])
{
    dijkstra_t* d = dijkstra;
    for (int i = 0; i < d->result_len; i++)
    {
        solution[i][0] = d->result[i].id;
        solution[i][1] = d->result[i].cost;
        solution[i][0] = d->result[i].predecessor;
    }

    return true;
}

//Save graph to txt file
_Bool dijkstra_save_path(const void *dijkstra, const char *filename)
{
    save_txt(dijkstra, filename);
    return true;
}

//Free memory
void dijkstra_free(void *dijkstra)
{
    dijkstra_t* d = dijkstra;
    free(d->edges);

    free(d->heap->order);
    free(d->heap->indexes);
    free(d->heap->data);

    free(d->heap);

    for (int i = 0; i <= d->max_point; i++)
    {
        free(d->successors[i].dests);
    }

    free(d->successors);

    free(d->result);
}
