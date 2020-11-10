#include <omp.h>
#include <stdio.h>

int main (){

    omp_set_num_threads(8); // Setear el número de hebras a utilizar.
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        printf("Thread %d de %d\n", id, nt);
    }
    return 0;
}