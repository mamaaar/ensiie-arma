/* gcc -Wall -Wextra -lrt -msse2 -O2 ex1.c -o sumex1 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <x86intrin.h>

#ifndef N
  #define N 32
#endif

double A[N][N];
double B[N][N];
double C[N][N];

void mul() {
  int i, j, k;
  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      for (k = 0; k < N; ++k) {
	C[i][j] += A[i][k]*B[k][j];
      }
    }
  }
}

int main() {
    struct timespec t0, t1;
    double tmp;

    assert (N%2 == 0);

#ifdef DEBUG
    for (int i=0; i<N; ++i)
    {
    	A[i] = drand48();
    	B[i] = drand48();
    	C[i] = 0.0;
    }
#endif

    clock_gettime(CLOCK_REALTIME, &t0);
    mul();
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
