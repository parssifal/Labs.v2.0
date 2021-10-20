#include <stdio.h>
#ifndef GRAPH
#define GRAPH

struct Item;

typedef struct Node {
    int busy;
    int x, y;
    char *str;
    struct Item *item;
} Node;

typedef struct Item {
    int ind;
    int w; //вес ребра
    struct Item *next;
} Item;

typedef struct Graph {
    int k; //количество вершин
    Node *mas;
} Graph;

typedef struct _DFS_ {
    int color;
    int d, f; //discover and finish time
    int pred; //индекс предшественника
} _DFS_;

typedef struct _BellFord_ {
    int d; //distance
    int pred;
} _BellFord_;

typedef struct Way {
    int k;
    int *mas;
} Way;

int add_node(Graph *graph, int x, int y, char *str);
int delete_node(Graph *graph, char *str);
int add_edge(Graph *graph, char *str1, char *str2, int w);
int delete_edge(Graph *graph, char *str1, char *str2);
void DFS_visit(Graph *graph, _DFS_ *dfs, int ind1, int ind2, int *time);
int DFS(Graph *graph, Way *way, char *str1, char *str2);
int BellFord(Graph *graph, Way *way, char *str1, char *str2);
void find_3_min_index(Graph *graph, int **d, int a[3], int b[3]);
int Floyd_Warshall(Graph *graph, Way way[3]);
void show_graph(Graph *graph);
void show_way(Graph *graph, Way *way);
void graphviz_show(Graph *graph);
void delete_graph(Graph *graph);
int create_random(Graph *graph, int size);
int file_write(char *name, Graph *graph);
int file_read(char *name, Graph *graph);
#endif
