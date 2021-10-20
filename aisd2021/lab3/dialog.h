#include <stdio.h>
#include "table.h"
#ifndef DIALOG_H
#define DIALOG_H
int D_add(Table *table);
int D_delete(Table *table);
int D_find(Table *table);
int D_find_one(Table *table, Index *index);
int D_find_par(Table *table, Table *table2);
int D_delete_one(Table *table);
#endif

