#ifndef TREE_H
#define TREE_H
#include <stdio.h>
typedef struct Node {
    char *key;
    char *info;
    struct Node *par;
    struct Node *left;
    struct Node *right;
    struct Node *next;
} Node;

typedef struct Tree {
    Node *root;
} Tree;

typedef struct Address {
    int k;
    Node **mas;
} Address;

typedef struct Words {
    int k; //number of words
    int *count; //count of same words in tree
    char **mas;
} Words;

Node *node_new();
Node *find_min(Node *node);
Node *find_max(Node *node);
int find_min_all(Tree *tree, Address *address);
Node *find_next(Node *node);
Node *find_prev(Node *node);
int find(Tree *tree, char *key, Address *address);
void find_count_of_words(Tree *tree, Words *words);
void show_words(Words *words);
int insert(Tree *tree, char *key, char *info);
int delete_node(Tree *tree, char *key, int num);
void show(Node *node);
void format_show(Node *node, int space);
void graphviz_show(Node *node);
void show_founded(Address *address);
void write_tree(FILE *file, Node *node);
int file_write(char *name, Tree *tree);
int file_read(char *name, Tree *tree);
int make_words_and_insert_in_tree(Tree *tree, char *str);
void delete_tree(Node *node);
void delete_words(Words *words);
#endif
