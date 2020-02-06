#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "rcm.h"

void init_vertex( const int n, const double A[], Vertex V[], Vertex* v ) {
		int k = 0;
		v->neighbors = malloc(n*sizeof(int*));
		for(int i = 0; i < n; i++) {
			if( A[i] != 0 && i != v->id ) {
				v->neighbors[k++] = i;
			}
		}
		v->degree = k;
		v->neighbors = realloc(v->neighbors, k*sizeof(int));
		v->visited = false;
		return;
}

int main (int argc, char** argv) {

	int n = atoi(argv[1]),
			R[n];
	double *A = malloc(n*sizeof(double)),
					time;
	Vertex V[n];
	FILE *in = fopen("data.in", "rb");


	for( int v = 0; v < n; v++ ) {
		fread(A, sizeof(double), n, in); 
		V[v].id = v; 
		init_vertex(n,A,V,&V[v]);
	}

	fclose(in);
	free(A);
	
	time = omp_get_wtime();
	rcm(n,V,R);
	time = omp_get_wtime() - time;

	FILE *out = fopen("data.out", "wb");
	fwrite(&time, sizeof(double), 1, out);
	fclose(out);

	return 0;
}
