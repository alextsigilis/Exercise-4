#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "rcm.h"

unsigned int* Deg;

int cmp( const void *a, const void *b ) {
	
	int i = *(unsigned int*)a,
			j = *(unsigned int*)b;

	return ( Deg[i] - Deg[j] );

}

int minDegreeVertex( size_t n ) {
	
	int min = 0;
	for( size_t v = 1; v < n; v++ )
		if( Deg[min] > Deg[v] ) 
			min = v;
	return min;

}

void rcm( const size_t n, const double *A, unsigned int *R ) {

	Deg = malloc(n*sizeof(unsigned int));
	unsigned int N[n][n],
							 visited[n],
							 k = 0;

	
	// Create the neighborhood of each 
	for( size_t v = 0; v < n; v++ ) {
		
		Deg[v] = 0;

		for( int i = 0; i < n; i++ ) {
				if( Amat(v,i) != 0 && v != i ) {
					N[v][ Deg[v]++ ] = i;
				}
		}

		visited[v] = 0;
	}

	Queue* Q = init(2*n);
	push( Q, minDegreeVertex(n) );

	while( !empty(Q) ) {
		
		unsigned int v = pop(Q);

		R[k++] = v;
		visited[v] = 1;
		
		qsort(N[v], Deg[v], sizeof(unsigned int), cmp);

		for( size_t i = 0; i < Deg[v]; i++)
			if( ! visited[ N[v][i] ] )
				push( Q, N[v][i] );

	}

}
