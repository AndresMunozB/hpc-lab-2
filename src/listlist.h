#ifndef LISTLIST_HEADER
#define LISTLIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct ListList
{
    unsigned long len;
    List *data;
} ListList;

ListList *ll_create();
void ll_print(ListList *listlist);
void ll_append(ListList *listlist, List new_element);   
void ll_delete(ListList *listlist, unsigned long index);
float ll_pop_min(ListList *listlist);
int ll_is_empty(ListList *listlist);
void ll_merge(ListList *listlist, List *list);
void ll_free(ListList *listlist);

#endif