#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

// IMPLEMENTACION BASADA EN: https://www.cimat.mx/~alram/comp_algo/clase17.pdf
Item item_create(float number, unsigned long block)
{
    Item item;
    item.number = number;
    item.block = block;
    return item;
}

void item_print(Item item)
{
    printf("Number: %f\n", item.number);
    printf("Block: %lu\n", item.block);
}

Heap *heap_create(unsigned long size)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->data = (Item *)malloc(sizeof(Item) * size);
    heap->size = size;
    heap->last = 0;
    return heap;
}

void heap_free(Heap *heap)
{
    free(heap->data);
    free(heap);
}

void heap_print(Heap *heap)
{
    for (unsigned long i = 0; i < heap->last; i++)
        item_print(heap->data[i]);
    printf("\n");
}

void heap_exchange(Heap *heap, unsigned long i, unsigned long j)
{
    Item temp = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = temp;
}

void heap_fix_up(Heap *heap, unsigned long k)
{
    while (k > 0 && heap->data[k / 2].number > heap->data[k].number)
    {
        heap_exchange(heap, k, k / 2);
        k = k / 2;
    }
}

void heap_fix_down(Heap *heap, unsigned long k)
{
    while (2 * k <= heap->last - 1)
    {
        unsigned long j = 2 * k;
        if (j < heap->last - 1 && heap->data[j].number > heap->data[j + 1].number)
            j++;

        if (!(heap->data[k].number > heap->data[j].number))
            break;
        heap_exchange(heap, k, j);
        k = j;
    }
}

void heap_insert(Heap *heap, Item item)
{
    heap->data[heap->last++] = item;
    heap_fix_up(heap, heap->last - 1);
}

Item heap_pop(Heap *heap)
{
    if(heap->last == 1){
        heap->last--;
        return heap->data[0];
    }
    Item min = heap->data[0];
    heap_exchange(heap, 0, heap->last - 1);
    heap->last--;
    heap_fix_down(heap, 0);
    return min;
}
