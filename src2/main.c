#include "functions.h"
#include "utils.h"

int main()
{
    
    char* name_file = "../data/64floats.raw";
    unsigned long size = 64l;
    float* numbers = (float *)aligned_alloc(16, sizeof(float) * size);
    
    read_file(name_file, numbers, size); // LEER ARCHIVO
    
    simd_sort(numbers,size);
    multiway_sort(numbers,size);
    print_float_array(numbers,size);
}