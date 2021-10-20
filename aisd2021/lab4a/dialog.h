#ifndef DIALOG_H
#define DIALOH_H
#include <stdio.h>
#include "tree.h"
int D_add(Tree *tree);
int D_add_random(Tree *tree);
int D_find(Tree *tree, Address *address);
int D_find_min(Tree *tree, Address *address);
int D_delete(Tree *tree);
int D_write_file(Tree *tree);
int D_read_file(Tree *tree);
#endif
