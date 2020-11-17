#include "functions.h"
#include "utils.h"

int main()
{
    
    char* name_file = "../data/65536floats.raw";
    unsigned long size = 65536l;
    float* numbers = (float *)aligned_alloc(16, sizeof(float) * size);
    
    read_file(name_file, numbers, size); // LEER ARCHIVO
    
    simd_sort(numbers,size);
    multiway_sort(numbers,size);
    omp_sort(numbers, size, 4,2);
    print_float_array(numbers,size);
    free(numbers);
}