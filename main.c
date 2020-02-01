#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "rcm.h"

int main (int argc, char** argv) {
	
	int n = atoi(argv[1]);

	double *A = malloc(n*n*sizeof(double));;	
	FILE *in = fopen("data.in", "rb");
	fread(A, sizeof(double), n*n, in);
	fclose(in);

	int *R = malloc(n * sizeof(int));

	rcm(n,A,R);

	FILE *out = fopen("data.out", "wb");
	fwrite(R, sizeof(int), n, out);
	fclose(out);

	return 0;
}
