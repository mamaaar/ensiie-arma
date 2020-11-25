/* 
gcc -Wall -Wextra -lrt -msse2 -O2 sum_sse2.c -o sum_sse2
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <x86intrin.h>

#define DEBUG

#ifndef N
  #define N 3200
#endif


char A[N];
char B[N];
char C[N];


/* __m128i _mm_loadu_si128 (__m128i const* mem_addr) */
/* void _mm_storeu_si128 (__m128i* mem_addr, __m128i a) */

void somme() {
    for (int i = 0; i < N; ++i)
    {
        __m128i ai = _mm_set1_epi8( A[i] );
        __m128i bi = _mm_set1_epi8( B[i] );
    
        _mm_store_si128 (&C[i], _mm_add_epi8(ai, bi));
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
    for (int i=0; i<N; ++i) {
        fprintf(stderr, "[ ");
        fprintf(stderr, "%d ", C[i]);
        fprintf(stderr, "]\n");
    }
#endif

    printf("%d %lf\n", N, tmp);
    return 0;
}



