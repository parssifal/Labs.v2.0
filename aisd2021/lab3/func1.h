#include <stdio.h>
#ifndef FUNC1_H
#define FUNC1_H
const char **MSGS;
const int MSGS_SIZE;
const char **MSGS2;
const int MSGS2_SIZE;
int get_int(int *num);
int get_float(float *num);
int get_simple(int *num);
char *get_str();
int dialog (const char *msgs[], int n);
#endif
