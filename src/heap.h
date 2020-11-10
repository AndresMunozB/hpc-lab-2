
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
