#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "rcm.h"

//! Initializes a vertex based on the adjacency matrix A
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
		v->level = INT_MAX;
		v->visited = false;
		return;
}

//! The main function.
int main (int argc, char** argv) {

	int n = atoi(argv[2]),
			*R = calloc(n,sizeof(int));
	double *A = malloc(n*sizeof(double));
	Vertex V[n];
	FILE *in = fopen("data.in", "rb");


	for( int v = 0; v < n; v++ ) {
		fread(A, sizeof(double), n, in); 
		V[v].id = v; 
		init_vertex(n,A,V,&V[v]);
	}

	fclose(in);
	free(A);

	if( argv[1][1] == 'S' ){
		printf("Running sequentialy...\n");
		rcm(n,V,R);
	}
	else {
		printf("Runnin in parallel...\n");
		parallel_rcm(n,V,R);
	}

	FILE *out = fopen("data.out", "wb");
	fwrite(R, sizeof(int), n, out);
	fclose(out);

	return 0;
}
