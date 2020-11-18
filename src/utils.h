#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
# include <ctype.h>
# include <unistd.h>

void read_file(char *file_name, float *array, unsigned long size);
void write_file(char *file_name, float *array, unsigned long size);
void print_float_array(float *array, unsigned long size);
unsigned long pow2(int exp);
int get_opt(int argc, char *argv[], char **i, char **o, unsigned long *n, int *d);

#endif
