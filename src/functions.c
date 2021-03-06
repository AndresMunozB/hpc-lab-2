#include "functions.h"
#include "heap.h"
#include <omp.h>
#include <string.h>
#include "utils.h"

void swap(__m128 *r1, __m128 *r2)
{
    __m128 t1;
    t1 = _mm_shuffle_ps(*r1, *r1, _MM_SHUFFLE(3, 2, 1, 0));
    *r1 = _mm_shuffle_ps(*r2, *r2, _MM_SHUFFLE(3, 2, 1, 0));
    *r2 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(3, 2, 1, 0));
}

//GENERA 4 BLOQUES DE 4 NUMEROS ORDENADOS DE MENOR A MAYOR
void sort_in_register(__m128 *r1, __m128 *r2, __m128 *r3, __m128 *r4)
{
    //REGISTROS TEMPORALES
    __m128 p11, p12, p13, p14, p22, p23;

    //PRIMERO PASO
    p11 = _mm_min_ps(*r1, *r3);
    p12 = _mm_min_ps(*r2, *r4);
    p13 = _mm_max_ps(*r1, *r3);
    p14 = _mm_max_ps(*r2, *r4);

    //SEGUNDO PASO
    *r1 = _mm_min_ps(p11, p12); //FINAL
    p22 = _mm_max_ps(p11, p12);
    p23 = _mm_min_ps(p13, p14);
    *r4 = _mm_max_ps(p13, p14); //FINAL

    //TERCER PASO
    *r2 = _mm_min_ps(p22, p23); //FINAL
    *r3 = _mm_max_ps(p22, p23); //FINAL

    //TRASPONER LA MATRIZ
    _MM_TRANSPOSE4_PS(*r1, *r2, *r3, *r4);
}

// GENERA UN BLOQUE DE 8 NUMEROS ORDENADO DE MENOR A MAYOR
void bmn_network(__m128 *r1, __m128 *r2)
{
    __m128 t1, t2;

    // PRIMER PASO
    *r1 = _mm_shuffle_ps(*r1, *r1, _MM_SHUFFLE(3, 1, 2, 0)); // INVERTIR AL MEDIO
    *r2 = _mm_shuffle_ps(*r2, *r2, _MM_SHUFFLE(0, 2, 1, 3)); // INVERTIR LOS EXTREMOS

    t1 = _mm_max_ps(*r1, *r2);
    t2 = _mm_min_ps(*r1, *r2);

    // SEGUNDO PASO
    *r1 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(2, 0, 2, 0));
    *r2 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(3, 1, 3, 1));
    *r1 = _mm_shuffle_ps(*r1, *r1, _MM_SHUFFLE(3, 1, 2, 0)); // INVERTIR AL MEDIO
    *r2 = _mm_shuffle_ps(*r2, *r2, _MM_SHUFFLE(3, 1, 2, 0)); // INVERTIR AL MEDIO

    t1 = _mm_max_ps(*r1, *r2);
    t2 = _mm_min_ps(*r1, *r2);

    // TERCER PASO
    *r1 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(1, 0, 1, 0));
    *r2 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(3, 2, 3, 2));
    *r1 = _mm_shuffle_ps(*r1, *r1, _MM_SHUFFLE(3, 1, 2, 0)); // INVERTIR AL MEDIO
    *r2 = _mm_shuffle_ps(*r2, *r2, _MM_SHUFFLE(3, 1, 2, 0)); // INVERTIR AL MEDIO

    t1 = _mm_max_ps(*r1, *r2);
    t2 = _mm_min_ps(*r1, *r2);

    // FINAL

    *r1 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(3, 2, 3, 2));
    *r2 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(1, 0, 1, 0));
    *r1 = _mm_shuffle_ps(*r1, *r1, _MM_SHUFFLE(0, 2, 1, 3)); // INVERTIR EXTREMOS
    *r2 = _mm_shuffle_ps(*r2, *r2, _MM_SHUFFLE(0, 2, 1, 3)); // INVERTIR EXTREMOS
}

//GENERA UN BLOQUE DE 16 NUMEROS ORDENADOS DE MENOR A MAYOR
void merge_simd(__m128 *r1, __m128 *r2, __m128 *r3, __m128 *r4)
{
    bmn_network(r1, r3);

    if (_mm_comile_ss(*r2, *r4))
    { //Si r4[0]>r2[0]
        bmn_network(r3, r2);
        bmn_network(r2, r4);
        swap(r2, r3);
    }
    else
    {
        bmn_network(r3, r4);
        bmn_network(r4, r2);
        swap(r3, r2);
        swap(r3, r4);
    }
}

//GENERA UNA LISTA ORDENADA DE NUMEROS
void simd_sort(float *numbers, unsigned long size)
{
    unsigned long counter = 0l;
    __m128 r1, r2, r3, r4;

    for (unsigned long i = 0; i < size / 16; i++)
    {
        //CARGAR REGISTROS
        r1 = _mm_load_ps(numbers + (i * 16) + 0);
        r2 = _mm_load_ps(numbers + (i * 16) + 4);
        r3 = _mm_load_ps(numbers + (i * 16) + 8);
        r4 = _mm_load_ps(numbers + (i * 16) + 12);

        //ORDENAMIENTO DE LOS 16 ELEMENTOS
        sort_in_register(&r1, &r2, &r3, &r4); // 4 NUMEROS EN CADA REGISTRO ORDENADO DE MENOS A MAYOR
        bmn_network(&r1, &r2);                // 8 NUMEROS ORDENADOS DE MENOS A MAYOR EN DOS REGISTROS
        bmn_network(&r3, &r4);                // 8 NUMEROS ORDENADOS DE MENOS A MAYOR EN DOS REGISTROS
        merge_simd(&r1, &r2, &r3, &r4);       // 16 NUERMOS ORDENADOS DE MENOR A MAYOR EN 4 REGISTROS

        //SE GUARDAN LOS REGISTROS
        _mm_store_ps(numbers + (i * 16) + 0, r1);
        _mm_store_ps(numbers + (i * 16) + 4, r2);
        _mm_store_ps(numbers + (i * 16) + 8, r3);
        _mm_store_ps(numbers + (i * 16) + 12, r4);
        counter++;
    }
}

void multiway_sort(float *numbers, unsigned long size)
{
    float *numbers_aux = (float *)malloc(sizeof(float) * size);
    int *flags = (int *)calloc(size, sizeof(int));
    unsigned long index = 0l;
    Heap *heap = heap_create((size / 16) + 16); // SI SIZE ES MENOR QUE 16 RETORNA 0 (ERROR DE MEMORIA)
    Item item_aux;
    for (unsigned long i = 0; i < size; i += 16)
    {
        heap_insert(heap, item_create(numbers[i], i));
        flags[i] = 1;
    }
    while (heap->last != 0)
    {
        item_aux = heap_pop(heap);
        numbers_aux[index++] = item_aux.number;
        flags[item_aux.block] = 1;
        if (item_aux.block + 1 < size && !flags[item_aux.block + 1])
            heap_insert(heap, item_create(numbers[item_aux.block + 1], item_aux.block + 1));
    }
    for (unsigned long i = 0; i < size; i++)
        numbers[i] = numbers_aux[i];

    heap_free(heap);
    free(numbers_aux);
    free(flags);
}

void merge(float *numbers, unsigned long size)
{
    float *numbers_aux = (float *)malloc(sizeof(float) * size);
    unsigned long half = size / 2;
    unsigned long left_count = 0;
    unsigned long right_count = half;
    unsigned long index = 0;

    while (left_count < half && right_count < size)
    {
        if (numbers[left_count] > numbers[right_count])
            numbers_aux[index++] = numbers[right_count++];
        else
            numbers_aux[index++] = numbers[left_count++];
    }
    while (left_count < half)
        numbers_aux[index++] = numbers[left_count++];
    while (right_count < size)
        numbers_aux[index++] = numbers[right_count++];

    for (unsigned long i = 0; i < size; i++)
        numbers[i] = numbers_aux[i];
    free(numbers_aux);
    return;
}

void omp_sort(float *array, unsigned long size, int levels, int threads)
{
    omp_set_num_threads(threads);
    #pragma omp parallel
    #pragma omp single nowait
    sort_aux(array, size, levels);
}

void sort_aux(float *array, unsigned long size, int levels)
{
    if (levels == 0 || size <= 16) //CASO BORDE
    {
        simd_sort(array, size); // SI NO ENTRA UN ARREGLO MULTIPLO DE 16 SE
        multiway_sort(array, size);
        return;
    }
    unsigned long half = size / 2;

    #pragma omp task untied //ORDENAR MITAD IZQUIERDA
    {
        sort_aux(array, half, levels - 1);
    }
    #pragma omp task untied //ORDENAR MITAD DERECHA
    {
        sort_aux(array + half, half, levels - 1);
    }
    #pragma omp taskwait
    merge(array, size);
}