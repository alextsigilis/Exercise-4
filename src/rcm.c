#include <stdlib.h>
#include <limits.h>
#include "rcm.h"


void findDegree( const size_t n, const double *A, unsigned int *deg ) {
	
	for( size_t v = 0; v < n; v++ ) {
		deg[v] = 0;
		for( size_t i = 0; i < n; i++) {
			deg[v] += (Amat(v,i) != 0)? 1 : 0;
		}

	}

}

void rcm( const size_t n, const double *A, unsigned int *R ) {

	unsigned int *deg = malloc(n*sizeof(unsigned int));

	findDegree( n, A, deg );

	
	

}
