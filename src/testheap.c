#include "heap.h"

int main()
{
    int size = 10000;
    Heap *heap = heap_create(size); // SI SIZE ES MENOR QUE 16 RETORNA 0 (ERROR DE MEMORIA)
    for (int i = 0; i < size; i++)
    {
        heap_insert(heap, item_create(i, i));
    }
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            heap_exchange(heap, i, j);

    for (int i = 0; i < size; i++)
    {
        Item item = heap_pop(heap);
    }
    heap_free(heap);
    return 0;
}