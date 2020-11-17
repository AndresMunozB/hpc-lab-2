#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

#include "functions.h"

void recorrer(float array[], int length, int numLevels);
void mostrar(float array[], int length);

void inicio(float *arrayNumbers, int length, int numThreads)
{

    int numLevels = 3;
    omp_set_num_threads(numThreads);
    #pragma omp parallel
    #pragma omp single nowait
    recorrer(arrayNumbers, length, numLevels); //dividir el arreglo en n niveles
}

void suma(float *arrayNumbers, int length)
{
    for (int i = 0; i < length; ++i)
    {
        arrayNumbers[i] = arrayNumbers[i] + 1;
    }
}

void recorrer(float *arrayNumbers, int length, int numLevels)
{

    //Caso borde en que se llega al nivel más profundo pedido, se realiza ordenamiento SIMD
    if (numLevels == 0)
    {
        int i;
        for (i = 0; i < length; i += 16)
        {
            suma(arrayNumbers, length); //simd
        }

        //Se realiza el multyway sort usando el heap
        mostrar(arrayNumbers, length); //multiway_sort()
        return;
    }

    //Caso que el arreglo tiene más de 16 elementos (n*16, con n >= 2)
    int mitad = length / 2;

    #pragma omp task untied
    {
        //Ordeno la mitad izquierda
        recorrer(arrayNumbers, mitad, numLevels - 1);
    }
    #pragma omp task untied
    {
        //Ordeno la mitad derecha
        recorrer(arrayNumbers + mitad, mitad, numLevels - 1);
    }

    //Hago que se espere a terminar las dos task
    #pragma omp taskwait
    //merge();
}

void mostrar(float array[], int length)
{
    printf("los valores son: \n");
    for (int i = 0; i < length; ++i)
    {
        printf("%f \n", array[i]);
    }
}

int main(int argc, char *argv[])
{

    char *pathFileIn;
    char *pathFileOut;
    int N, l;
    char debug;
    N = 4;  //hebras
    l = 32; //largo
    float arrayNumbers[l];
    for (int i = 0; i < l; ++i)
    {
        arrayNumbers[i] = rand() % (l);
    }

    printf("los valores son: \n");
    for (int i = 0; i < l; ++i)
    {
        printf("%f \n", arrayNumbers[i]);
    }

    inicio(arrayNumbers, l, N);

    return 0;
}