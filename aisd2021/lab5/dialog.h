#include <stdio.h>
#ifndef DIALOG
#define DIALOG
#include "graph.h"
int D_add_node(Graph *graph);
int D_add_edge(Graph *graph);
int D_delete_node(Graph *graph);
int D_delete_edge(Graph *graph);
int D_create_random(Graph *graph);
int D_DFS(Graph *graph);
int D_BellFord(Graph *graph);
int D_Floyd_Warshall(Graph *graph);
int D_write_file(Graph *graph);
int D_read_file(Graph *graph);
#endif
