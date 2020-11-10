#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include <xmmintrin.h> /* SSE __m128 float */
#include "list.h"
#include "listlist.h"

void swap(__m128 *r1, __m128 *r2);
void sort_in_register(__m128 *r1, __m128 *r2, __m128 *r3, __m128 *r4);
void bmn_network(__m128 *r1, __m128 *r2);
void merge_simd(__m128 *r1, __m128 *r2,__m128 *r3, __m128 *r4);
void simd_sort(List *list, List *list_sorted, int debug);
void swap_float(float *xp, float *yp);
void bubble_sort(float arr[], int n, int debug);

#endif
