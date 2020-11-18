#include "functions.h"
#include "utils.h"

int main()
{

    char *name_file = "../data/65536floats.raw";
    char *output_name_file = "65536floatssorted.raw";
    unsigned long size = 65536l;
    int threads = 4;
    int levels = 2;

    float *numbers = (float *)aligned_alloc(16, sizeof(float) * size); // SE SOLICITA MEMORIA PARA LOS NUMEROS A ORDENAR
    read_file(name_file, numbers, size);         // LEER ARCHIVO
    omp_sort(numbers, size, levels, threads);    // SORT THE NUMBERS
    write_file(output_name_file, numbers, size); //ESCRIBIR LOS DATOS ORDENADOS
    free(numbers); // SE LIBERA LA MEMORIA UTILIZADA PARA LOS NUMEROS
}