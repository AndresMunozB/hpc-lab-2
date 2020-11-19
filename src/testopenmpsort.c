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
    if (get_opt(argc, argv, &name_file, &output_name_file, &size, &dValue, &levels, &threads) == 0)
        return 0;
    /*
    printf("name_file: %s\n", name_file);
    printf("output_name_file: %s\n", output_name_file);
    printf("size %lu\n", size);
    printf("threads: %d\n", threads);
    printf("levels: %d\n", levels);
    printf("dValue: %d\n", dValue);
    */
    
    float *numbers = (float *)aligned_alloc(16, sizeof(float) * size); // SE SOLICITA MEMORIA PARA LOS NUMEROS A ORDENAR
    int iterations = 10;
    double *times = (double *)malloc(sizeof(double) * iterations);
    for (int i = 0; i < iterations; i++)
    {
        printf("leer\n");
        read_file(name_file, numbers, size);                                 // LEER ARCHIVO

        clock_t t = clock();                                                 // SE COMIENZA A MEDIR EL TIEMPO

        printf("omp_sort\n");
        printf("levels: %d\n", levels);
        printf("threads: %d\n", threads);
        omp_sort(numbers, size, levels, threads);                            // SORT THE NUMBERS

        double time_taken = ((double)(clock() - t)) / CLOCKS_PER_SEC;        // SE TERMINA DE MEDIR EL TIEMPO

        printf("times\n");
        times[i] = time_taken;
        printf("simd_sort() took %f seconds to execute \n", time_taken);

        printf("2\n");
    }
    write_file_normal(output_name_file, times, iterations);                       // ESCRIBIR LOS DATOS ORDENADOS
    printf("\n");
    printf("Termino .. %s \n \n",output_name_file);
    free(numbers);                                                    // SE LIBERA LA MEMORIA UTILIZADA PARA LOS NUMEROS
    free(times);
    return 0;
}