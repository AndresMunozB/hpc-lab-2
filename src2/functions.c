#include "functions.h"

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
void simd_sort(float* numbers, unsigned long size)
{
    unsigned long counter = 0l;
    unsigned long steps = size / 16;
    
    for (unsigned long i = 0; i < size / 16; i++)
    {
        __m128 r1, r2, r3, r4;
        //CARGAR REGISTROS
        r1 = _mm_load_ps(numbers + (i * 16) + 0);
        r2 = _mm_load_ps(numbers + (i * 16) + 4);
        r3 = _mm_load_ps(numbers + (i * 16) + 8);
        r4 = _mm_load_ps(numbers + (i * 16) + 12);

        sort_in_register(&r1, &r2, &r3, &r4); // 4 NUMEROS EN CADA REGISTRO ORDENADO DE MENOS A MAYOR
        bmn_network(&r1, &r2); // 8 NUMEROS ORDENADOS DE MENOS A MAYOR EN DOS REGISTROS
        bmn_network(&r3, &r4); // 8 NUMEROS ORDENADOS DE MENOS A MAYOR EN DOS REGISTROS
        merge_simd(&r1, &r2, &r3, &r4); // 16 NUERMOS ORDENADOS DE MENOR A MAYOR EN 4 REGISTROS
        
        //SE GUARDAN LOS REGISTROS
        _mm_store_ps(numbers + (i * 16) + 0, r1);
        _mm_store_ps(numbers + (i * 16) + 4, r2);
        _mm_store_ps(numbers + (i * 16) + 8, r3);
        _mm_store_ps(numbers + (i * 16) + 12, r4);
        counter ++;
    }    
}

