#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
# include <ctype.h>
# include <unistd.h>

void read_file(char *file_name, float *array, unsigned long size);
void write_file(char *file_name, float *array, unsigned long size);
void create_file(char *file_name, unsigned long size);
void print_float_array(float *array, int size);
void print_matrix_16(float *arg1, float *arg2, float *arg3, float *arg4);
int get_opt(int argc, char *argv[], char **i, char **o, unsigned long *n, int *d);

#endif
