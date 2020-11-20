#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include <xmmintrin.h> /* SSE __m128 float */

void swap(__m128 *r1, __m128 *r2);
void sort_in_register(__m128 *r1, __m128 *r2, __m128 *r3, __m128 *r4);
void bmn_network(__m128 *r1, __m128 *r2);
void merge_simd(__m128 *r1, __m128 *r2, __m128 *r3, __m128 *r4);
void simd_sort(float* numbers, unsigned long size);
void multiway_sort(float* numbers, unsigned long size);
void omp_sort(float *array, unsigned long size, int levels, int threads);
void sort_aux(float *array, unsigned long size, int levels);
#endif
