#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

Heap *create_heap(unsigned long size)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->data = (Item *)malloc(sizeof(Item) * size);
    heap->size = size;
    heap->last = 0;
    return heap;
}

void free_heap(Heap *heap)
{
    free(heap->data);
    free(heap);
}

Item create_item(float number, unsigned long block)
{
    Item item;
    item.number = number;
    item.block = block;
    return item;
}

void print_item(Item item)
{
    printf("Number: %f\n", item.number);
    printf("Block: %lu\n", item.block);
}

void print_heap(Heap *heap)
{
    for (unsigned long i = 0; i < heap->last; i++)
        print_item(heap->data[i]);
    printf("\n");
}

void exchange(Heap *heap, unsigned long i, unsigned long j)
{
    Item temp = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = temp;
}

void fix_up(Heap *heap, unsigned long k)
{
    while (k > 0 && heap->data[k / 2].number > heap->data[k].number)
    {
        exchange(heap, k, k / 2);
        k = k / 2;
    }
}

void fix_down(Heap *heap, unsigned long k)
{
    while (2 * k <= heap->last - 1)
    {
        unsigned long j = 2 * k;
        if (j < heap->last - 1 && heap->data[j].number > heap->data[j + 1].number)
            j++;

        if (!(heap->data[k].number > heap->data[j].number))
            break;
        exchange(heap, k, j);
        k = j;
    }
}

void insert(Heap *heap, Item item)
{
    heap->data[heap->last++] = item;
    fix_up(heap, heap->last - 1);
}

Item pop_min(Heap *heap)
{
    Item min = heap->data[0];
    exchange(heap, 0, heap->last - 1);
    heap->last--;
    fix_down(heap, 0);
    return min;
}
/*
int main()
{
    Item item1 = create_item(1.0, 1l);
    Item item2 = create_item(2.0, 3l);
    Item item3 = create_item(3.0, 2l);
    Item item4 = create_item(4.0, 4l);
    //print_item(item);
    Heap *heap = create_heap(4l);
    insert(heap, item2);
    insert(heap, item3);

    insert(heap, item1);
    insert(heap, item4);
    print_heap(heap);
    printf("\n");
    Item min = pop_min(heap);
    print_heap(heap);
    printf("\n");
    print_item(min);
    printf("\n");
    Item item0 = create_item(0.0, 1l);
    insert(heap, item0);
    print_heap(heap);
    free_heap(heap);
    return 0;
}*/