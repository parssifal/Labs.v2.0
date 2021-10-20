#ifndef TREE
#define TREE
#include <stdio.h>
#include <stdlib.h>
typedef struct Info {
    float f;
    char *str;
    struct Info *next;
} Info;

typedef struct Node {
    int size;
    unsigned int key[3];
    Info *info[3];
    struct Node *par;
    struct Node *first;
    struct Node *second;
    struct Node *third;
    struct Node *fourth;
} Node;

typedef struct Near {
    unsigned int key;
    Info *info;
} Near;

typedef struct Tree {
    Node *root;
} Tree;

void swap_keys(unsigned int *a, unsigned int *b);
void swap_info(Info *a, Info *b);
void sort_2(unsigned int *a, unsigned int *b, Info *x, Info *y);
void sort_3(unsigned int *a, unsigned int *b, unsigned int *c, Info *x, Info *y, Info *z);
void sort_keys(Node *node);
int is_leaf(Node *node);
Node *new_node(unsigned int k, Info *info);
void insert_to_node(Node *node, unsigned int k, Info *info);
void become_node1(Node *node, unsigned int k, Info *info, Node *x, Node *y);
Node *split(Node *item);
Node *insert(Node *ptr, unsigned int k, Info *info);
Node *search(Node *ptr, unsigned int k);
Node *search_min(Node *ptr);
void remove_from_node(Node *ptr, unsigned int k, int status);
Node *redistribute(Node *leaf);
Node *merge(Node *leaf);
Node *fix(Node *leaf);
Node *remove_tree(Node *ptr, unsigned int k);
Info *find(Node *ptr, unsigned int k);
void find_near(Node *ptr, unsigned int k, Near *near, unsigned int *dist);
void show(Node *node);
void graphviz_show(Node *node);
void format_show(Node *node, int space);
void show_range_direct(Node *node, unsigned int a, unsigned int b);
void show_range_reverse(Node *node, unsigned int a, unsigned int b);
void write_tree(FILE *file, Node *node);
int file_write(char *name, Tree *tree);
int file_read(char *name, Tree *tree);
void delete_tree(Node *node);
#endif



