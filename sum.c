/* gcc -Wall -Wextra -lrt -msse2 -O2 sum.c -o sum */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <x86intrin.h>

#ifndef N
  #define N 3200
#endif


char A[N];
char B[N];
char C[N];

void somme() {
	int i;

	for (i = 0; i < N; ++i)
	{
		C[i] = A[i] + B[i];
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
