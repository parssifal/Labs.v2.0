#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>

int get_int(int *num);
char *get_str();
char *file_str(FILE *file);
char *random_str(int len);
int dialog (const char *msgs[], int n);
#endif
