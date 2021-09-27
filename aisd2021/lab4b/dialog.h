#ifndef DIALOG
#define DIALOG
#include <stdio.h>
#include "tree.h"
int D_add(Tree *tree);
int D_add_random(Tree *tree);
int D_delete(Tree *tree);
int D_find(Tree *tree);
int D_find_near(Tree *tree);
int D_show_range(Tree *tree);
int D_write_file(Tree *tree);
int D_read_file(Tree *tree);
#endif

