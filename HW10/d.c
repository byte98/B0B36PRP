
#include "d.h"

int main(int argc, char *argv[])
{
    int reti = 0;

    void* dijkstra = dijkstra_init();
    dijkstra_load_graph("some-in.txt", dijkstra);
    printf(BBLUE "[INFO " BLUE "%s:%i" BBLUE "]" BLUE " Data from file has been loaded\n", __FILE__, __LINE__);
    /*int edges[5][3] = {
            {0, 1, 2},
            {2, 1, 5},
            {0, 2, 8},
            {1, 0, 8},
            {1, 2, 5}
    };
    dijkstra_set_graph(5, edges, dijkstra);*/
    //print_dijkstra(dijkstra);
    dijkstra_solve(dijkstra, 0);
    dijkstra_save_path(dijkstra, "solved-out.txt");
    dijkstra_free(dijkstra);
    //print_dijkstra(dijkstra);
    return reti;
}

#include "_d_h.c"