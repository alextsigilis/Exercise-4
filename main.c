#include <stdio.h>
#include <stdlib.h>
#include "rcm.h"

int main () {
	
	size_t n = 10;
	double *A = malloc(n*n * sizeof(double));
	unsigned int *R = malloc(n * sizeof(unsigned int));

	rcm(n,A,R);

	printf("Hello, world\n");

	return 0;
}
