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
/*
int main()
{
    Item item1 = item_create(1.0, 1l);
    Item item2 = item_create(2.0, 3l);
    Item item3 = item_create(3.0, 2l);
    Item item4 = item_create(4.0, 4l);
    //item_print(item);
    Heap *heap = heap_create(4l);
    heap_insert(heap, item2);
    heap_insert(heap, item3);
    heap_insert(heap, item1);
    heap_insert(heap, item4);
    heap_print(heap);
    printf("\n");
    Item min = heap_pop(heap);
    min = heap_pop(heap);
    min = heap_pop(heap);
    min = heap_pop(heap);
    heap_print(heap);
    printf("\n");
    item_print(min);
    printf("\n");
    Item item0 = item_create(0.0, 1l);
    heap_insert(heap, item0);
    heap_print(heap);
    heap_free(heap);
    return 0;
}*/