#include "functions.h"
#include "utils.h"
#include <time.h>

int main(int argc, char *argv[])
{
    char *name_file = NULL;
    char *output_name_file = NULL;
    unsigned long size;
    int threads;
    int levels;
    int dValue;

    //SE OBTIENEN Y VALIDAN LOS DATOS DE ENTRADA
    if (get_opt(argc, argv, &name_file, &output_name_file, &size, &dValue, &levels, &threads) == 0)
        return 0; // TERMINAR EJECUCIÓN POR ERROR EN LOS PARÁMETROS

    float *numbers = (float *)aligned_alloc(16, sizeof(float) * size); // SE SOLICITA MEMORIA PARA LOS NUMEROS A ORDENAR
    read_file(name_file, numbers, size);                               // LEER ARCHIVO
    omp_sort(numbers, size, levels, threads);                          // ORDENAMIENTO CON OPENMP
    write_file(output_name_file, numbers, size);                       //ESCRIBIR LOS DATOS ORDENADOS
    if (dValue)
        print_float_array(numbers, size);
    free(numbers); // SE LIBERA LA MEMORIA UTILIZADA PARA LOS NUMEROS
    return 0;
}