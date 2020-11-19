#include <time.h>
#include "functions.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    // PARAMETROS DE ENTRADA
    char *name_file = NULL;
    char *output_name_file = NULL;
    unsigned long size;
    int threads;
    int levels;
    int dValue;
    if (get_opt(argc, argv, &name_file, &output_name_file, &size, &dValue, &threads, &levels) == 0)
        return 0;

    float *numbers = (float *)aligned_alloc(16, sizeof(float) * size); // SE SOLICITA MEMORIA PARA LOS NUMEROS A ORDENAR
    read_file(name_file, numbers, size);                               // LEER ARCHIVO
    
    for (int i = 0; i < 20; i++)
    {
        clock_t t = clock();                                               // SE COMIENZA A MEDIR EL TIEMPO
        omp_sort(numbers, size, levels, threads);                          // SORT THE NUMBERS
        double time_taken = ((double)(clock() - t)) / CLOCKS_PER_SEC;      // SE TERMINA DE MEDIR EL TIEMPO
        write_file(output_name_file, numbers, size);                       //ESCRIBIR LOS DATOS ORDENADOS
        printf("simd_sort() took %f seconds to execute \n", time_taken);
    }
    
    free(numbers);                                                     // SE LIBERA LA MEMORIA UTILIZADA PARA LOS NUMEROS
    return 0;
}