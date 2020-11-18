#include "functions.h"
#include "utils.h"

int main()
{

    char *name_file = "../data/64floats.raw";
    unsigned long size = 64l;

    float *numbers = (float *)aligned_alloc(16, sizeof(float) * size);
    
    read_file(name_file, numbers, size); // LEER ARCHIVO

    for (int i =0;i<1000;i++){
        printf("i: %d\n", i);
        omp_sort(numbers, size, 2, 2);
    }

    free(numbers);
}