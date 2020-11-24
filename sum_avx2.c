/* gcc -Wall -Wextra -lrt -mavx2 -O2 sum_avx2.c -o sum_avx2 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <x86intrin.h>

#ifndef N
  #define N 160
#endif


__m256i A[N];
__m256i B[N];
__m256i C[N];


/* 2.2
__m128i _mm_loadu_si128 (__m128i const* mem_addr)
void _mm_storeu_si128 (__m128i* mem_addr, __m128i a) */

/* 2.3
__m256i _mm256_load_si256 (__m256i const * mem_addr)
void _mm256_store_si256 (__m256i * mem_addr, __m256i a)
*/

void somme() {
    for (int i = 0; i < N; ++i)
    {
        __m256i atemp = _mm256_load_si256( &A[i] );
        __m256i btemp = _mm256_load_si256( &B[i] );
        _mm256_store_si256 ( &C[i], _mm256_add_epi64(atemp,btemp));

    }

}

int main() {
    struct timespec t0, t1;
    double tmp;

    assert (N%16 == 0);

    srand( time( NULL ) );

#ifdef DEBUG
    for (int i=0; i<N; ++i)
    {
        A[i] = rand();
        B[i] = rand();
        C[i] = 0.0;
    }
#endif

    clock_gettime(CLOCK_REALTIME, &t0);
    somme();
    clock_gettime(CLOCK_REALTIME, &t1);
    tmp = 1000.*(t1.tv_sec-t0.tv_sec) + (t1.tv_nsec-t0.tv_nsec)/1000000. ;

#ifdef DEBUG
    for (i=0; i<N; ++i) {
        fprintf(stderr, "[ ");
        fprintf(stderr, "%d ", C[i]);
        fprintf(stderr, "]\n");
    }
#endif

    printf("%d %lf\n", N, tmp);
    return 0;
}