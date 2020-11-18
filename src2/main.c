#include "functions.h"
#include "utils.h"

int main()
{

    char *name_file = "../data/64floats.raw";
    unsigned long size = 64l;

    float *numbers = (float *)aligned_alloc(16, sizeof(float) * size);
    
    

    //simd_sort(numbers, size);
    //multiway_sort(numbers,size);

    for (int i =0;i<1000;i++){
        printf("i: %d\n", i);
        read_file(name_file, numbers, size); // LEER ARCHIVO
        omp_sort(numbers, size, 2, 2);
        //print_float_array(numbers,size);
    }
    
    
    free(numbers);
}