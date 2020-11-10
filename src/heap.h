
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


Item item_create(float number, unsigned long block);
void item_print(Item item);
Heap *heap_create(unsigned long size);
void heap_free(Heap *heap);
void heap_print(Heap *heap);
void heap_exchange(Heap *heap, unsigned long i, unsigned long j);
void heap_fix_up(Heap *heap, unsigned long k);
void heap_fix_down(Heap *heap, unsigned long k);
void heap_insert(Heap *heap, Item item);
Item heap_pop(Heap *heap);
