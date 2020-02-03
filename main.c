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

	/*for(int i = 0; i < n; i++) {

		for(int j = 0; j < n; j++) printf("%f ", Amat(i,j));
		printf("\n");
	}
	printf("\n");*/

	int *R = calloc(n , sizeof(int));

	rcm(n,A,R);

	/*for(int i = 0; i<n; i++) {
		printf("%d\n", R[i]);
	}*/

	FILE *out = fopen("data.out", "wb");
	fwrite(R, sizeof(int), n, out);
	fclose(out);

	return 0;
}
