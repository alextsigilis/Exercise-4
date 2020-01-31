#include <stdio.h>
#include <stdlib.h>
#include "rcm.h"

int main () {
	
	size_t n = 5;


	double A[] = 		{ 1, 0, 0, 1, 1,
										0, 1, 0, 0, 1,
										0, 0, 1, 0, 1,
										1, 0, 0, 1, 1,
										1, 1, 1, 1, 1
									};


	unsigned int *R = malloc(n * sizeof(unsigned int));

	rcm(n,A,R);

	for(size_t i = 0; i < n; i++)
		printf("%d\n", R[i]);

	return 0;
}
