#include "functions.h"
#include "utils.h"
#include <time.h>

int main()
{

    char *name_file = "../data/160000floats.raw";
    char *output_name_file = "160000floatssorted.raw";
    unsigned long size = 160000l;
    int threads = 4;
    int levels = 2;

    float *numbers = (float *)aligned_alloc(16, sizeof(float) * size); // SE SOLICITA MEMORIA PARA LOS NUMEROS A ORDENAR
    read_file(name_file, numbers, size);                               // LEER ARCHIVO
    clock_t t = clock();                                               // SE COMIENZA A MEDIR EL TIEMPO
    omp_sort(numbers, size, levels, threads);                          // SORT THE NUMBERS
    double time_taken = ((double)(clock() - t)) / CLOCKS_PER_SEC;      // SE TERMINA DE MEDIR EL TIEMPO
    write_file(output_name_file, numbers, size);                       //ESCRIBIR LOS DATOS ORDENADOS
    free(numbers);                                                     // SE LIBERA LA MEMORIA UTILIZADA PARA LOS NUMEROS
    printf("simd_sort() took %f seconds to execute \n", time_taken);
}