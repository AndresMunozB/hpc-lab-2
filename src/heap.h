
typedef struct Item
{
    float number;        //NUMERO
    unsigned long block; //BLOQUE AL QUE PERTENERCE EL NUMERO
} Item;

typedef struct Heap
{
    Item *data;
    unsigned long size;
    unsigned long last;
} Heap;

Heap *create_heap(unsigned long size);
void free_heap(Heap *heap);
Item create_item(float number, unsigned long block);
void print_item(Item item);
void print_heap(Heap *heap);
void exchange(Heap *heap, unsigned long i, unsigned long j);
void fix_up(Heap *heap, unsigned long k);
void fix_down(Heap *heap, unsigned long k);
void insert(Heap *heap, Item item);
Item pop_min(Heap *heap);