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

    int iterations = 31;
    float *numbers = (float *)aligned_alloc(16, sizeof(float) * size); // SE SOLICITA MEMORIA PARA LOS NUMEROS A ORDENAR
    for (int z = 2; z < 20; z++)
    {
        for (int j = 1; j < 40; j+=4)
        {
            double *times = (double *)malloc(sizeof(double) * iterations);
            for (int i = 0; i < iterations; i++)
            {
                read_file(name_file, numbers, size); // LEER ARCHIVO
                struct timespec begin, end;
                clock_gettime(CLOCK_REALTIME, &begin);
                omp_sort(numbers, size, levels, threads); // SORT THE NUMBERS
                clock_gettime(CLOCK_REALTIME, &end);
                long seconds = end.tv_sec - begin.tv_sec;
                long nanoseconds = end.tv_nsec - begin.tv_nsec;
                double elapsed = seconds + nanoseconds * 1e-9;
                printf("TEST #%d: Time measured: %.3f seconds. (%s) %dL %dT\n", i, elapsed, name_file, z, j);
                times[i] = elapsed;
            }
            sprintf(output_name_file, "%lu_%dl_%dh.csv", size, z, j);
            printf("%s\n", output_name_file);
            write_file_normal(output_name_file, times, iterations); // ESCRIBIR LOS DATOS ORDENADOS
            free(times);
        }
    }

    free(numbers); // SE LIBERA LA MEMORIA UTILIZADA PARA LOS NUMEROS
    return 0;
}