#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h> /* SSE __m128 float */

typedef struct List
{
    unsigned long len;
    float *data;
} List;

List *list_create();
List *list_init(unsigned long elements);
void list_print(List *list);
void list_free(List *list);
void list_append(List *list, float new_element);
float list_pop(List *list);
void list_load(List *list, __m128 r1);

#endif